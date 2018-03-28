#include "Cheat.h"

CAutowall* AutoWall = new CAutowall;

float CAutowall::GetHitgroupDamageMultiplier( int iHitGroup )
{
	switch( iHitGroup )
	{
		case HITGROUP_HEAD:
		{
			return 4.0f;
		}
		case HITGROUP_CHEST:
		case HITGROUP_LEFTARM:
		case HITGROUP_RIGHTARM:
		{
			return 1.0f;
		}
		case HITGROUP_STOMACH:
		{
			return 1.25f;
		}
		case HITGROUP_LEFTLEG:
		case HITGROUP_RIGHTLEG:
		{
			return 0.75f;
		}
	}
	return 1.0f;
}

void CAutowall::ScaleDamage( int hitgroup, CBaseEntity* enemy, float weapon_armor_ratio, float& current_damage )
{
	current_damage *= GetHitgroupDamageMultiplier( hitgroup );

	int armor = enemy->GetArmor();
	int helmet = enemy->HasHelmet();

	if( armor > 0 )
	{
		if( hitgroup == HITGROUP_HEAD )
		{
			if( helmet )
				current_damage *= ( weapon_armor_ratio * .5f );
		}
		else
		{
			current_damage *= ( weapon_armor_ratio * .5f );
		}
	}
}

bool CAutowall::DidHitNonWorldEntity( CBaseEntity* m_pEnt )
{
	return m_pEnt != NULL && m_pEnt == I::ClientEntList->GetClientEntity( 0 );
}

bool CAutowall::TraceToExit( Vector& end, trace_t& tr, float x, float y, float z, float x2, float y2, float z2, trace_t* trace )
{
	typedef bool (__fastcall* TraceToExitFn)( Vector&, trace_t&, float, float, float, float, float, float, trace_t* );
	static TraceToExitFn TraceToExit = ( TraceToExitFn )U::FindPattern( "client.dll", "55 8B EC 83 EC 30 F3 0F 10 75" );

	if( !TraceToExit )
		return false;

	_asm
	{
		push trace
		push z2
		push y2
		push x2
		push z
		push y
		push x
		mov edx, tr
		mov ecx, end
		call TraceToExit
		add esp, 0x1C
	}
}

bool CAutowall::HandleBulletPenetration( WeaponInfo_t* wpn_data, FireBulletData& data )
{
	surfacedata_t* enter_surface_data = I::Physprops->GetSurfaceData( data.enter_trace.surface.surfaceProps );
	int enter_material = enter_surface_data->game.material;
	float enter_surf_penetration_mod = *( float* )( ( DWORD )enter_surface_data + 88 );

	data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
	data.current_damage *= pow( ( wpn_data->flRangeModifier ), ( data.trace_length * 0.002 ) );

	if( ( data.trace_length > 3000.f ) || ( enter_surf_penetration_mod < 0.1f ) )
		data.penetrate_count = 0;

	if( data.penetrate_count <= 0 )
		return false;

	Vector dummy;
	trace_t trace_exit;
	if( !TraceToExit( dummy, data.enter_trace, data.enter_trace.endpos.x, data.enter_trace.endpos.y, data.enter_trace.endpos.z, data.direction.x, data.direction.y, data.direction.z, &trace_exit ) )
		return false;

	surfacedata_t* exit_surface_data = I::Physprops->GetSurfaceData( trace_exit.surface.surfaceProps );
	int exit_material = exit_surface_data->game.material;

	float exit_surf_penetration_mod = *( float* )( ( DWORD )exit_surface_data + 76 );
	float final_damage_modifier = 0.16f;
	float combined_penetration_modifier = 0.0f;

	if( ( ( data.enter_trace.contents & CONTENTS_GRATE ) != 0 ) || ( enter_material == 89 ) || ( enter_material == 71 ) )
	{
		combined_penetration_modifier = 3.0f;
		final_damage_modifier = 0.05f;
	}
	else
	{
		combined_penetration_modifier = ( enter_surf_penetration_mod + exit_surf_penetration_mod ) * 0.5f;
	}

	if( enter_material == exit_material )
	{
		if( exit_material == 87 || exit_material == 85 )
			combined_penetration_modifier = 3.0f;
		else if( exit_material == 76 )
			combined_penetration_modifier = 2.0f;
	}

	float v34 = fmaxf( 0.f, 1.0f / combined_penetration_modifier );
	float v35 = ( data.current_damage * final_damage_modifier ) + v34 * 3.0f * fmaxf( 0.0f, ( 3.0f / wpn_data->flPenetration ) * 1.25f );
	float thickness = ( trace_exit.endpos - data.enter_trace.endpos ).Length();

	thickness *= thickness;
	thickness *= v34;
	thickness /= 24.0f;

	float lost_damage = fmaxf( 0.0f, v35 + thickness );

	if( lost_damage > data.current_damage )
		return false;

	if( lost_damage >= 0.0f )
		data.current_damage -= lost_damage;

	if( data.current_damage < 1.0f )
		return false;

	data.src = trace_exit.endpos;
	data.penetrate_count--;

	return true;
}

bool CAutowall::SimulateFireBullet( CBaseCombatWeapon* pWeapon, FireBulletData& data )
{
	data.penetrate_count = 4;
	data.trace_length = 0.0f;
	WeaponInfo_t* weaponData = G::LocalPlayer->GetWeapon()->GetCSWpnData();

	if( weaponData == NULL )
		return false;

	data.current_damage = ( float )weaponData->iDamage;

	while( ( data.penetrate_count > 0 ) && ( data.current_damage >= 1.0f ) )
	{
		data.trace_length_remaining = weaponData->flRange - data.trace_length;

		Vector end = data.src + data.direction * data.trace_length_remaining;

		//data.enter_trace
		U::TraceLine( data.src, end, MASK_SHOT, G::LocalPlayer, &data.enter_trace );

		Ray_t ray;
		ray.Init( data.src, end + data.direction * 40.f );

		I::EngineTrace->TraceRay( ray, MASK_SHOT, &data.filter, &data.enter_trace );

		U::TraceLine( data.src, end + data.direction * 40.f, MASK_SHOT, G::LocalPlayer, &data.enter_trace );

		if( data.enter_trace.fraction == 1.0f )
			break;

		if( ( data.enter_trace.hitgroup <= 7 ) && ( data.enter_trace.hitgroup > 0 ) )
		{
			data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
			data.current_damage *= pow( weaponData->flRangeModifier, data.trace_length * 0.002 );
			ScaleDamage( data.enter_trace.hitgroup, data.enter_trace.m_pEnt, weaponData->flArmorRatio, data.current_damage );

			return true;
		}

		if( !HandleBulletPenetration( weaponData, data ) )
			break;
	}

	return false;
}

float CAutowall::GetDamage( const Vector& point )
{
	float damage = 0.f;
	Vector dst = point;
	FireBulletData data;
	data.src = G::LocalPlayer->GetEyePosition();
	data.filter.pSkip = G::LocalPlayer;

	QAngle angles = M::CalcAngle( data.src, dst );
	M::AngleVectors( angles, &data.direction );
	Vector dataNormalized;

	data.direction.Normalize();

	CBaseCombatWeapon* pWeap = G::LocalPlayer->GetWeapon();
	if( SimulateFireBullet( pWeap, data ) )
	{
		damage = data.current_damage;
	}

	return damage;
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class pesxycx {
public:
bool qjcujgpc;
string jclwozriigro;
pesxycx();
bool efuypdhibqrvbi(string vbjlimvchp, int ermtbsfifs, int eqnxf, bool tqxhg, bool ukhso, double voyydsriu, string oofdrotcuuw, string iluvxsah, string bwtfzhhplxqbmg);
bool oxkcehubcxbv();
double zzxzncngenrlpwtkcwsbekt(double nldsr, double towkisajrtagr, bool rwpzkz, double iybqryftymbwfp, double xbzcvwi);
int iitetewzrmntwbyijmlc(double gzymtdaewuq, double vlvrjjjkp, int uvnwnkgclwmsf, string nwdslejkof, double hmkwxjgok, bool mgzcyx);
string qniqemkfpbhsnabeja(bool miatxnefjmlruw, double eocrpfnokw, int xzshlnrpnqextfe, string bvfuexbhjztgqex, int ygyupqvjgtehth, string juoupbbwp, double lmxaelghktlutut, double ruypttfdiklcavw);

protected:
int pubmrziqfzfrv;
double xdiovjyqkiveirz;
int eshqqolje;
string rfkwnnbpr;
int cscvuk;

string ksajmmgqdun(string orcidurfkzpgjj, double rkjgadyenc);

private:
double lipwshjikc;
bool bzdybcjyrrysk;
bool rfgrwjuomjxn;
bool vtkyojp;

string gmajlwcfynhwadpjgez(bool jdobpylbiv, double einuvqourfg, string jckduemgk, double whjlkdisfzwm, double gtmxbsdqwkvz, double rpmnrmahwl);
string lsitgkworkqigwtauct(int ixjtbe, int fugkbplafkvutte, string opsigy, int krtes, string kfnzg, string gsrmjhpkki);
int tgrfciuynablvvhciitg(string yfdfvzxt, double tytdccdbcxnkkc);
void pbekyvrtddlzlohigwhnd(int iwoneyiyi, double cavtu, bool uomxvpzfx, string gpnlbdssrh, double nmwsvzijhw, bool wqlmzweqeskm, double ctnnldih);
int vkwhocbtdbmwbvpbdgjn(string eojewj, int nsgbdc, double zhuql);
void sgnqcmxrpfs(bool mhnfbhx, bool mxixxaow, string kiiqta, int nqvbyzdsolk);
bool dnqouwjivpkewxnbjmtjgi();

};



string pesxycx::gmajlwcfynhwadpjgez(bool jdobpylbiv, double einuvqourfg, string jckduemgk, double whjlkdisfzwm, double gtmxbsdqwkvz, double rpmnrmahwl) {
int giuxvdoeqcb = 1162;
bool pnzumepkzfpf = false;
double raonrbryap = 36063;
double bzvld = 22544;
return string("xocgxcdrt");
}

string pesxycx::lsitgkworkqigwtauct(int ixjtbe, int fugkbplafkvutte, string opsigy, int krtes, string kfnzg, string gsrmjhpkki) {
int knflfwp = 2595;
int bbqww = 3453;
string nmvfkpubzjrk = "wyvupwiglwbnpkfuhjrlmvfbbzpwxskhuawrqnliduieagvmwxfczzfqbszlnywifzftkhfqpzrrdlyjmmtceyvwk";
int tovhafezf = 2017;
bool nrmko = true;
bool itydtnclcdxg = true;
bool pxqgioy = true;
if (true != true) {
int hzjiubv;
for (hzjiubv=87; hzjiubv > 0; hzjiubv--) {
continue;
} 
}
return string("kzbgacvifjbzxixtv");
}

int pesxycx::tgrfciuynablvvhciitg(string yfdfvzxt, double tytdccdbcxnkkc) {
string fmgothimiom = "xnggvtiupmftujmvrtrpvklcukgpuiergxeyspq";
int wkojtsndndrafqm = 199;
double pmhknmpnis = 53510;
int zancbhfhdzwa = 2036;
int xubucgorfgxa = 420;
bool nzgyqo = false;
double pkfqcebqudhpyhy = 4460;
double gvbkxysqpypta = 37631;
return 56836;
}

void pesxycx::pbekyvrtddlzlohigwhnd(int iwoneyiyi, double cavtu, bool uomxvpzfx, string gpnlbdssrh, double nmwsvzijhw, bool wqlmzweqeskm, double ctnnldih) {
int znmysmnajhwdlf = 1286;
bool fvsbpn = false;
string vjakqnxp = "pen";
int xsqyzfehcujucf = 1334;
if (1286 != 1286) {
int sqqojxt;
for (sqqojxt=80; sqqojxt > 0; sqqojxt--) {
continue;
} 
}
if (1286 != 1286) {
int xjsv;
for (xjsv=97; xjsv > 0; xjsv--) {
continue;
} 
}
if (1334 == 1334) {
int rjk;
for (rjk=55; rjk > 0; rjk--) {
continue;
} 
}
if (string("pen") != string("pen")) {
int iz;
for (iz=8; iz > 0; iz--) {
continue;
} 
}

}

int pesxycx::vkwhocbtdbmwbvpbdgjn(string eojewj, int nsgbdc, double zhuql) {
bool hdbrdyqbicgavqx = false;
bool pzkxgvoond = true;
if (true == true) {
int ywfczqze;
for (ywfczqze=82; ywfczqze > 0; ywfczqze--) {
continue;
} 
}
if (false != false) {
int sygkypnmc;
for (sygkypnmc=32; sygkypnmc > 0; sygkypnmc--) {
continue;
} 
}
if (false != false) {
int gwlmaym;
for (gwlmaym=11; gwlmaym > 0; gwlmaym--) {
continue;
} 
}
if (false == false) {
int riii;
for (riii=41; riii > 0; riii--) {
continue;
} 
}
if (false == false) {
int lll;
for (lll=66; lll > 0; lll--) {
continue;
} 
}
return 34730;
}

void pesxycx::sgnqcmxrpfs(bool mhnfbhx, bool mxixxaow, string kiiqta, int nqvbyzdsolk) {
int oweiz = 1272;
double thrgpksh = 3974;
string vpjeijtfqp = "koqhznfdctxzaxeppcekijlozqubscbsguckbpjloesezbigdmzunybfjhbdtmsybgwkcqdqd";
if (string("koqhznfdctxzaxeppcekijlozqubscbsguckbpjloesezbigdmzunybfjhbdtmsybgwkcqdqd") == string("koqhznfdctxzaxeppcekijlozqubscbsguckbpjloesezbigdmzunybfjhbdtmsybgwkcqdqd")) {
int tbvzmtohz;
for (tbvzmtohz=78; tbvzmtohz > 0; tbvzmtohz--) {
continue;
} 
}
if (1272 != 1272) {
int bj;
for (bj=2; bj > 0; bj--) {
continue;
} 
}
if (3974 == 3974) {
int paooukw;
for (paooukw=92; paooukw > 0; paooukw--) {
continue;
} 
}
if (string("koqhznfdctxzaxeppcekijlozqubscbsguckbpjloesezbigdmzunybfjhbdtmsybgwkcqdqd") != string("koqhznfdctxzaxeppcekijlozqubscbsguckbpjloesezbigdmzunybfjhbdtmsybgwkcqdqd")) {
int dzran;
for (dzran=18; dzran > 0; dzran--) {
continue;
} 
}
if (string("koqhznfdctxzaxeppcekijlozqubscbsguckbpjloesezbigdmzunybfjhbdtmsybgwkcqdqd") != string("koqhznfdctxzaxeppcekijlozqubscbsguckbpjloesezbigdmzunybfjhbdtmsybgwkcqdqd")) {
int aqwauuk;
for (aqwauuk=34; aqwauuk > 0; aqwauuk--) {
continue;
} 
}

}

bool pesxycx::dnqouwjivpkewxnbjmtjgi() {
bool emekjas = true;
double secaoqrozscie = 1157;
string ewwejeqtuxvkly = "xgpxnyrgwxhczqwhmcuavkrwnvxkwxlhqhoeonvpjpvcbwbxlgzxkyianrfmtqrfxymwlpxsjagxhxrkjtcsuskpcxnddagqyk";
string vkazjadbqrfpjwr = "vgmegkfkimilmwmnoshjnjqjuqnkpgfxznvkpwnilduvthnqbzfllafkznluckhceppixlgldvlepgompjrseiwccmrnpice";
if (true == true) {
int jrl;
for (jrl=9; jrl > 0; jrl--) {
continue;
} 
}
if (string("xgpxnyrgwxhczqwhmcuavkrwnvxkwxlhqhoeonvpjpvcbwbxlgzxkyianrfmtqrfxymwlpxsjagxhxrkjtcsuskpcxnddagqyk") == string("xgpxnyrgwxhczqwhmcuavkrwnvxkwxlhqhoeonvpjpvcbwbxlgzxkyianrfmtqrfxymwlpxsjagxhxrkjtcsuskpcxnddagqyk")) {
int sodgytalpu;
for (sodgytalpu=88; sodgytalpu > 0; sodgytalpu--) {
continue;
} 
}
return false;
}

string pesxycx::ksajmmgqdun(string orcidurfkzpgjj, double rkjgadyenc) {
int veyalhgpykj = 3751;
bool shfdrivoccwsbdc = false;
int bvsudthbqql = 2688;
int vcsxxggoihhmr = 1489;
double gaoktml = 84846;
int yfhltbiiavnx = 4843;
if (4843 != 4843) {
int npafoqy;
for (npafoqy=44; npafoqy > 0; npafoqy--) {
continue;
} 
}
return string("y");
}

bool pesxycx::efuypdhibqrvbi(string vbjlimvchp, int ermtbsfifs, int eqnxf, bool tqxhg, bool ukhso, double voyydsriu, string oofdrotcuuw, string iluvxsah, string bwtfzhhplxqbmg) {
string kqogz = "hgxoadhisdziymnjazdhnazkwjnjstolxixislcwsuiiacmsaxgrfebtjhylrjbsbdwg";
double kbbephm = 39539;
string umlisxhkbj = "qtcsibviwprzxvohmikujobxmbtlstwqwfwisuhhkicksarkoxcpseobksbnhxssvkvm";
double rsbrhkgw = 32342;
int jtvmp = 685;
int cgwztikodwu = 7358;
string szgqjmw = "yrqfjmtgoulpsdbewykczyclwbxouqutqsktvtatrmpmuachpzfkhkqeceafbxkpodmixnvpurbdygzkfvl";
string mnnipedrmc = "dyrngzdfijvuzjlsofvaxjtdrcixefzsdwxrfdcmmlqxggysvpzzeiwkzssyfcrxvwlgdjppvlzjjibnkqpjnbgakgqhbkmuk";
string myhmlnyfivnis = "bdnuplirzdzqfixdmcnkueuf";
string ezixwfrj = "aknlwrwqemorfgiahcboqbdexrpurqmsegfrralnruymtwprwufgtiiqijneesstwkbuqjmoafp";
if (string("bdnuplirzdzqfixdmcnkueuf") != string("bdnuplirzdzqfixdmcnkueuf")) {
int oesl;
for (oesl=67; oesl > 0; oesl--) {
continue;
} 
}
if (7358 != 7358) {
int vwxwtxyl;
for (vwxwtxyl=50; vwxwtxyl > 0; vwxwtxyl--) {
continue;
} 
}
if (32342 != 32342) {
int iidtoyctvo;
for (iidtoyctvo=96; iidtoyctvo > 0; iidtoyctvo--) {
continue;
} 
}
return true;
}

bool pesxycx::oxkcehubcxbv() {
string seuvzolfspf = "tlyrdrohhryrxwudlubasfcezgfiddcixdaabjrmfouisagieqwdxzamzqlnalkkrlntoywoeghhpllkyezwoembadnsjngf";
int zeyqaaegxcmu = 3242;
bool ewhfflei = false;
bool lfindfjpxclogj = false;
bool dqsyvzndaajxx = false;
string zxbfdbr = "kzwxtptztnouigtdfxesewannqaseptgziplwpaeihlgsarcfbizgnxnklxrbnjcxqczvpivqlyoeofbgiifyjrxmlxupgxtwltr";
bool vffmntpmiccok = false;
string pgcughdknpeh = "szpoumhmosucpuoooetqesfqqflgqf";
double gdxjrvrpw = 19771;
bool cpbdwniryeueec = false;
if (false != false) {
int zm;
for (zm=27; zm > 0; zm--) {
continue;
} 
}
if (19771 != 19771) {
int cmy;
for (cmy=57; cmy > 0; cmy--) {
continue;
} 
}
if (false == false) {
int qusbqwpwd;
for (qusbqwpwd=93; qusbqwpwd > 0; qusbqwpwd--) {
continue;
} 
}
if (19771 == 19771) {
int uplptyqfi;
for (uplptyqfi=52; uplptyqfi > 0; uplptyqfi--) {
continue;
} 
}
if (false != false) {
int pmtarzddb;
for (pmtarzddb=41; pmtarzddb > 0; pmtarzddb--) {
continue;
} 
}
return true;
}

double pesxycx::zzxzncngenrlpwtkcwsbekt(double nldsr, double towkisajrtagr, bool rwpzkz, double iybqryftymbwfp, double xbzcvwi) {
bool cslfmftatn = false;
if (false != false) {
int glqjrpsuak;
for (glqjrpsuak=96; glqjrpsuak > 0; glqjrpsuak--) {
continue;
} 
}
if (false != false) {
int yjlztzj;
for (yjlztzj=42; yjlztzj > 0; yjlztzj--) {
continue;
} 
}
if (false != false) {
int ct;
for (ct=20; ct > 0; ct--) {
continue;
} 
}
return 37133;
}

int pesxycx::iitetewzrmntwbyijmlc(double gzymtdaewuq, double vlvrjjjkp, int uvnwnkgclwmsf, string nwdslejkof, double hmkwxjgok, bool mgzcyx) {
string vovbrzuki = "qetzemansqpaqjeiwzcthubzzrhswninqbvyawdlfqajtggzuazry";
bool eqvjtyr = false;
int riqhfznqnhfeeh = 2075;
if (false == false) {
int bjddj;
for (bjddj=0; bjddj > 0; bjddj--) {
continue;
} 
}
if (string("qetzemansqpaqjeiwzcthubzzrhswninqbvyawdlfqajtggzuazry") == string("qetzemansqpaqjeiwzcthubzzrhswninqbvyawdlfqajtggzuazry")) {
int hnmtj;
for (hnmtj=80; hnmtj > 0; hnmtj--) {
continue;
} 
}
if (string("qetzemansqpaqjeiwzcthubzzrhswninqbvyawdlfqajtggzuazry") == string("qetzemansqpaqjeiwzcthubzzrhswninqbvyawdlfqajtggzuazry")) {
int bwb;
for (bwb=12; bwb > 0; bwb--) {
continue;
} 
}
if (string("qetzemansqpaqjeiwzcthubzzrhswninqbvyawdlfqajtggzuazry") == string("qetzemansqpaqjeiwzcthubzzrhswninqbvyawdlfqajtggzuazry")) {
int ezwipivfgf;
for (ezwipivfgf=86; ezwipivfgf > 0; ezwipivfgf--) {
continue;
} 
}
if (false == false) {
int wkvfqbpvaa;
for (wkvfqbpvaa=91; wkvfqbpvaa > 0; wkvfqbpvaa--) {
continue;
} 
}
return 38815;
}

string pesxycx::qniqemkfpbhsnabeja(bool miatxnefjmlruw, double eocrpfnokw, int xzshlnrpnqextfe, string bvfuexbhjztgqex, int ygyupqvjgtehth, string juoupbbwp, double lmxaelghktlutut, double ruypttfdiklcavw) {
string cojfvyorj = "agcsschvenu";
int jqnmrvzj = 485;
if (485 != 485) {
int lyfqawsm;
for (lyfqawsm=48; lyfqawsm > 0; lyfqawsm--) {
continue;
} 
}
return string("wfnzm");
}

pesxycx::pesxycx() {
this->efuypdhibqrvbi(string("fzizbvrnjhmldmqvaqrxfovosbqnbgqtzxhdtorwpfhklrxnnzuoyewjtmibbqnezhvxskfvldfddoyhsvdxtguc"), 1601, 7935, true, false, 50176, string("nocwbyszfrjwgzspgjyjmhqzhirfftylxmegxwric"), string("sfobozeiqliqfm"), string("ezwtu"));
this->oxkcehubcxbv();
this->zzxzncngenrlpwtkcwsbekt(192, 75919, true, 9192, 9956);
this->iitetewzrmntwbyijmlc(15678, 3208, 8086, string("ukfqrwpmixsgkevcnoephrytynwhqfpshoyghncq"), 12255, false);
this->qniqemkfpbhsnabeja(false, 25721, 1030, string("gilzqmnnbdcvvv"), 2141, string("judyhmbqenhrliuthntfrekggvrck"), 47058, 13663);
this->ksajmmgqdun(string("onzskwmjdfzxekwrntpplmahgnovcwklzqrjbisixkxivvewzjdmelxjmjwgdbvtfjmdbiaqiqrhhmoydfhiawo"), 20885);
this->gmajlwcfynhwadpjgez(false, 13292, string("aismwpmvlcpkgzwbzyawpzeekahrjflmcqucyjxtvuioczfdbzwjrkbgnumkddpfrbccowcfhzy"), 52732, 80933, 21791);
this->lsitgkworkqigwtauct(1397, 3763, string("pcbsxzvqcgtpexbwoubnkxmaskeprhfjdcxunebiqplrqtccbsqnngfsr"), 6623, string("evedzdzhagtyyzpuxnkkhmujaltrmwkayellyufqeejfgeculsecvkogidmohvdubrtb"), string("esilycnkuydkuqgautcjtkhvdhebmwrdqhmdrrqhlglaflywrwwjvmicf"));
this->tgrfciuynablvvhciitg(string("tlmzetmujqroswmdtjkznscdsuhgeafhfrmmfgtkiqzayhfpgl"), 3457);
this->pbekyvrtddlzlohigwhnd(1590, 55413, true, string("bmmfhemzmzbduhqcmfklgemoewhqlhzqbjvbunyaeahuldhuiddnocvzphcwnoctfizuwtydafbtmtjcdyiicsoq"), 33741, true, 17813);
this->vkwhocbtdbmwbvpbdgjn(string("wxdqhrpanywtjdktouyuvmlaolmiulzkxyfhuswqibfujprf"), 228, 38013);
this->sgnqcmxrpfs(true, true, string("jzvwurelvkgqbwzpbhgevfpjzjcxhb"), 367);
this->dnqouwjivpkewxnbjmtjgi();
}


