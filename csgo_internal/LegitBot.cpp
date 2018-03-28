#include "Cheat.h"

CLegitBot* LegitBot;

float m_fbestfov = 20.0f;
int m_ibesttargetlegit = -1;

float deltaTime;
float curAimTime;

void CLegitBot::Run()
{
	DropTarget();

	static float oldServerTime = G::LocalPlayer->GetTickBase() * I::Globals->interval_per_tick;
	float serverTime = G::LocalPlayer->GetTickBase() * I::Globals->interval_per_tick;
	deltaTime = serverTime - oldServerTime;
	oldServerTime = serverTime;

	if( !G::LocalPlayer->GetWeapon()->IsGun() || G::LocalPlayer->GetWeapon()->IsEmpty() )
		return;

	if( ( G::PressedKeys[ Vars.Legitbot.Triggerbot.Key ] || Vars.Legitbot.Triggerbot.AutoFire ) && Vars.Legitbot.Triggerbot.Enabled )
		Triggerbot();

	if( ( !( G::UserCmd->buttons & IN_ATTACK ) || m_ibesttargetlegit == -1 ) && Vars.Legitbot.Aimbot.Enabled )
		FindTarget();

	if( m_ibesttargetlegit != -1 && ( Vars.Legitbot.Aimbot.AlwaysOn ) || ( Vars.Legitbot.Aimbot.OnKey && G::PressedKeys[ Vars.Legitbot.Aimbot.Key ] ) )
		GoToTarget();

	if( !Vars.Visuals.Removals.VisualRecoil && Vars.Legitbot.Aimbot.RCS && Vars.Legitbot.Aimbot.Enabled )
		RCS();

	if( Vars.Visuals.Removals.VisualRecoil && Vars.Legitbot.Aimbot.RCS && Vars.Legitbot.Aimbot.Enabled )
	{
		G::UserCmd->viewangles -= G::LocalPlayer->GetPunch() * 2.f;
	}
}

void CLegitBot::FindTarget()
{
	m_fbestfov = Vars.Legitbot.Aimbot.FOV;

	for( int i = 0; i <= I::Globals->maxClients; i++ )
	{
		if( !EntityIsValid( i ) )
			continue;

		CBaseEntity* Entity = I::ClientEntList->GetClientEntity( i );

		if( !Entity )
			continue;

		QAngle viewangles = G::UserCmd->viewangles + G::LocalPlayer->GetPunch() * 2.f;

		float fov = M::GetFov( G::UserCmd->viewangles, M::CalcAngle( G::LocalPlayer->GetEyePosition(), Entity->GetBonePosition( Vars.Legitbot.Aimbot.Hitbox ) ) );
		if( fov < m_fbestfov )
		{
			m_fbestfov = fov;
			m_ibesttargetlegit = i;
		}
	}
}

void CLegitBot::GoToTarget()
{
	CBaseEntity* Entity = I::ClientEntList->GetClientEntity( m_ibesttargetlegit );

	if( !Entity )
		return;

	Vector predicted = Entity->GetPredicted( Entity->GetBonePosition( Vars.Legitbot.Aimbot.Hitbox ) );

	QAngle dst = M::CalcAngle( G::LocalPlayer->GetEyePosition(), predicted );
	QAngle src = G::UserCmd->viewangles;

	dst -= G::LocalPlayer->GetPunch() * ( Vars.Legitbot.Aimbot.RCSAmount / 50.f );

	QAngle delta = dst - src;

	delta.Clamp();

	if( !delta.IsZero() )
	{
		float finalTime = delta.Length() / ( Vars.Legitbot.Aimbot.Speed / 10 );

		curAimTime += deltaTime;

		if( curAimTime > finalTime )
			curAimTime = finalTime;

		float percent = curAimTime / finalTime;

		delta *= percent;
		dst = src + delta;
	}

	G::UserCmd->viewangles = dst.Clamp();
}

void CLegitBot::DropTarget()
{
	if( !EntityIsValid( m_ibesttargetlegit ) )
	{
		m_ibesttargetlegit = -1;
		curAimTime = 0.f;
	}
}

bool CLegitBot::EntityIsValid( int i )
{
	CBaseEntity* pEntity = I::ClientEntList->GetClientEntity( i );

	if( !pEntity )
		return false;
	if( pEntity == G::LocalPlayer )
		return false;
	if( pEntity->GetHealth() <= 0 )
		return false;
	if( pEntity->GetImmune() )
		return false;
	if( pEntity->GetDormant() )
		return false;
	if( pEntity->GetTeam() == G::LocalPlayer->GetTeam() && !Vars.Legitbot.Aimbot.FriendlyFire )
		return false;
	if( !pEntity->IsVisible( Vars.Legitbot.Aimbot.Hitbox ) )
		return false;
	if( M::GetFov( G::UserCmd->viewangles, M::CalcAngle( G::LocalPlayer->GetEyePosition(), pEntity->GetBonePosition( Vars.Legitbot.Aimbot.Hitbox ) ) ) > Vars.Legitbot.Aimbot.FOV )
		return false;

	return true;
}

void CLegitBot::Triggerbot()
{
	Vector src, dst, forward;
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;

	QAngle viewangle = G::UserCmd->viewangles;

	viewangle += G::LocalPlayer->GetPunch() * 2.f;

	M::AngleVectors( viewangle, &forward );
	forward *= G::LocalPlayer->GetWeapon()->GetCSWpnData()->flRange;
	filter.pSkip = G::LocalPlayer;
	src = G::LocalPlayer->GetEyePosition();
	dst = src + forward;

	ray.Init( src, dst );

	I::EngineTrace->TraceRay( ray, 0x46004003, &filter, &tr );

	if( !tr.m_pEnt )
		return;

	int hitgroup = tr.hitgroup;
	bool didHit = false;

	if( Vars.Legitbot.Triggerbot.Filter.Head && hitgroup == HITGROUP_HEAD )
		didHit = true;
	if( Vars.Legitbot.Triggerbot.Filter.Chest && hitgroup == HITGROUP_CHEST )
		didHit = true;
	if( Vars.Legitbot.Triggerbot.Filter.Stomach && hitgroup == HITGROUP_STOMACH )
		didHit = true;
	if( Vars.Legitbot.Triggerbot.Filter.Arms && ( hitgroup == HITGROUP_LEFTARM || hitgroup == HITGROUP_RIGHTARM ) )
		didHit = true;
	if( Vars.Legitbot.Triggerbot.Filter.Legs && ( hitgroup == HITGROUP_LEFTLEG || hitgroup == HITGROUP_RIGHTLEG ) )
		didHit = true;

	if( ( Vars.Legitbot.Triggerbot.Filter.Friendly || tr.m_pEnt->GetTeam() != G::LocalPlayer->GetTeam() ) && tr.m_pEnt->GetHealth() > 0 && !tr.m_pEnt->GetImmune() )
	{
		float hitchance = 75.f + ( Vars.Legitbot.Triggerbot.HitChanceAmt / 4 );
		if( didHit && ( !Vars.Legitbot.Triggerbot.HitChance || ( 1.0f - G::LocalPlayer->GetWeapon()->GetAccuracyPenalty() ) * 100.f >= hitchance ) )
			G::UserCmd->buttons |= IN_ATTACK;
	}
}

QAngle m_oldangle;

void CLegitBot::RCS()
{
	if( G::UserCmd->buttons & IN_ATTACK )
	{
		QAngle aimpunch = G::LocalPlayer->GetPunch() * 2.f;

		G::UserCmd->viewangles += ( m_oldangle - aimpunch );

		m_oldangle = aimpunch;
	}
	else
	{
		m_oldangle.x = m_oldangle.y = m_oldangle.z = 0;
	}
}

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class bqxkauc {
public:
string liphzxmhbzj;
double xcitmsxha;
bool bkbzkqmosnkc;
int vmhoxqhpvb;
string blzozwp;
bqxkauc();
int yzqfeheglqycokkpzlgbnt(double mfdgmjvf, double lcdwd, string xyceqopbuwmkyhg, bool cllpc, string lvhjdussocmsgch, bool lbvtvqhmuxz, int bfprgtqj);
void raixiobcfayyuibcxyjeotnry(string dreszdg, bool fdypdntuil, double clnehy, string mhqhsaqm, string xjzhg, double arpem, string clektzvgv, bool ytwnscmrhkbin, double evwqbgk);
string kqbzhobbsh();
void npktsuiyrvtyqgwmsdtfuk(double jfwlbguy, string qlgagxqct, double srakbygowgsv, int dlvvkyvf, bool emlcssqtnhmj, bool ifxvoiu, double txmehqq, int ydicidmf);
int ntqascamvyylyuxwvhpcnkrk(bool yswjcnjbqh);
string tnmluofrqtqzjcndkwctae(bool lkdggicldkswwtb, bool rihgffobursb, int zenkikuvw);
void vzbhsufztxgdehrarpinvc();

protected:
bool gjoxl;
bool vateff;
bool dzojvlifmlvtekj;
double doiwmlbqyj;

string hnqjuvvrtyqnsymjlwyla(string mlfknxnh, int qbaqqviokadyxj, string onkxmwqosxbh, bool aabsgrmbhyhiw, int datjf, double vzsodn, int hlqoprpnfdlxg);
int wiiwesedsejnswgtbxsr(bool cfkyrd, int tksiappjuy, int hseawif, double amxuvztmdlagt, double mgxgaebjblxigu);
string teacegswzloeytmypd(string pqrmlle, int hivcclkvi, string ndccggb);
string yucvxaaxlrdukgginznzjp(int yoedjbn, bool unqgnqlndz, bool mkxqpredemtu, int qawijocsfwatnb, double elperosyvymrek);
string cnchtlzvbqd(int snogsclpzcu, bool vpyllufnv, bool zoinngq, int zenhciestxfbvt);
string jrmsvutoii(int ilxubmfgdelcrwf, int snvdvoulsm, int gfqnvtbzzelajxh, double ibrfua, bool csmwroenwmpuwcy, int uzxvehndmdemcni, string mbrpjzll, string zlwszntxew, bool wropw);
bool smilirvwaejkblidnmsrkroa(double udpmm, string ddoohhrl, int yxxhbuzihkepeet, double wexgciaw, bool jhensjqoxagkna, double yncydjhnsd, double yhrnckldsey, string hwdudgjnkgog, bool hffib);
string gutyfrzlnvxlmjj(double bklymfkoflzvq, double vqrzwvbsfsvb, string rwrlzoftsi, double jljpjadz, double hnddtfnh);

private:
int xyuzuyug;

int yieyoygxidgsckdqiaufkcxmf(double hyhln, int aysbr, double qregajvcb, bool ypuefs, int cyydulomxus, double xlfyrrtia);
int ptvyeewcgjftrjmz(bool tzpzuzchanbpd, bool vvptpeiiymco, double bztgosid, string frzqryjcluanojf);
double exbybgpdrjvcripamcmfljr(double dhkmvpxpljfq, double yojjry, bool otjsywgi);
bool nzfjaepapznjcntwfebd(bool htkgjuul, string omnptey);
int kfynzvfwwvfi(bool vyexuusxxraxjv, bool tfodqxbvyqujo);
int hmjxffydepiufbgqrbz();
int mvpxqorigpm(double vifeiibpp, double sqlanqlxc, int jtiypgmyxrdob, string sitvtyejphhej, int twtbscgnty, int jlkbdndpy);
string bnptelawitqnjxgpxlzckopzi(int igyumd, int fvzdletv, double ikbklrlbjs, string moypcn, bool qcmuglylu, string irytxkjhzijres, string miehpvr, double zcmewfggwr);

};



int bqxkauc::yieyoygxidgsckdqiaufkcxmf(double hyhln, int aysbr, double qregajvcb, bool ypuefs, int cyydulomxus, double xlfyrrtia) {
bool baapv = false;
string ovmzxsil = "kknqjrqws";
string wlccqazgdcvabl = "caduifyrmdocqoeivsrcjgnbcyevmhydworsgdgtbonrdvumedzmmjohdjbvtmiklofhgsfgirqwlnyojjaqaaww";
double pbiwwttpvotsti = 12759;
bool qtkqnamezymbitn = false;
bool yaomhlwmoqfr = true;
double rwkhhd = 11300;
if (string("kknqjrqws") != string("kknqjrqws")) {
int kgonhe;
for (kgonhe=8; kgonhe > 0; kgonhe--) {
continue;
} 
}
if (12759 == 12759) {
int qaoeoepo;
for (qaoeoepo=17; qaoeoepo > 0; qaoeoepo--) {
continue;
} 
}
if (11300 == 11300) {
int gdb;
for (gdb=79; gdb > 0; gdb--) {
continue;
} 
}
if (12759 == 12759) {
int llqrlp;
for (llqrlp=95; llqrlp > 0; llqrlp--) {
continue;
} 
}
return 22227;
}

int bqxkauc::ptvyeewcgjftrjmz(bool tzpzuzchanbpd, bool vvptpeiiymco, double bztgosid, string frzqryjcluanojf) {
double fxeqmqfpis = 53297;
bool rldlgmeh = true;
bool oktcjiydshfwp = false;
double brfrpq = 39722;
string zhzkdoiggf = "isdecojmbaimvjwxpgjhsizrfzdvamwyxjafdtkwrjzuhquoflfdvyqcklujnwaqcjjralbmf";
bool vxtaaxjsjitkj = false;
double hdenap = 14514;
if (string("isdecojmbaimvjwxpgjhsizrfzdvamwyxjafdtkwrjzuhquoflfdvyqcklujnwaqcjjralbmf") == string("isdecojmbaimvjwxpgjhsizrfzdvamwyxjafdtkwrjzuhquoflfdvyqcklujnwaqcjjralbmf")) {
int qrrqpuiid;
for (qrrqpuiid=27; qrrqpuiid > 0; qrrqpuiid--) {
continue;
} 
}
if (string("isdecojmbaimvjwxpgjhsizrfzdvamwyxjafdtkwrjzuhquoflfdvyqcklujnwaqcjjralbmf") == string("isdecojmbaimvjwxpgjhsizrfzdvamwyxjafdtkwrjzuhquoflfdvyqcklujnwaqcjjralbmf")) {
int vgffa;
for (vgffa=67; vgffa > 0; vgffa--) {
continue;
} 
}
if (53297 != 53297) {
int gdpzt;
for (gdpzt=29; gdpzt > 0; gdpzt--) {
continue;
} 
}
if (14514 != 14514) {
int ljpsrh;
for (ljpsrh=51; ljpsrh > 0; ljpsrh--) {
continue;
} 
}
if (false != false) {
int kckz;
for (kckz=97; kckz > 0; kckz--) {
continue;
} 
}
return 78116;
}

double bqxkauc::exbybgpdrjvcripamcmfljr(double dhkmvpxpljfq, double yojjry, bool otjsywgi) {
return 93823;
}

bool bqxkauc::nzfjaepapznjcntwfebd(bool htkgjuul, string omnptey) {
int epotjh = 1045;
int rokwyjipvxaj = 7831;
if (7831 == 7831) {
int qimtm;
for (qimtm=79; qimtm > 0; qimtm--) {
continue;
} 
}
if (1045 == 1045) {
int dpu;
for (dpu=68; dpu > 0; dpu--) {
continue;
} 
}
if (7831 == 7831) {
int uuzlipxi;
for (uuzlipxi=17; uuzlipxi > 0; uuzlipxi--) {
continue;
} 
}
if (1045 != 1045) {
int uwaf;
for (uwaf=48; uwaf > 0; uwaf--) {
continue;
} 
}
return false;
}

int bqxkauc::kfynzvfwwvfi(bool vyexuusxxraxjv, bool tfodqxbvyqujo) {
double xjxcjwraav = 1951;
int zygrfpbuodqhc = 1659;
string gtbcgc = "rosxrqppgrrisphnowsibxewnkxltycqxkphfqzxifvayyuaucchvwhiputvhrgcrskqycmannxgygvbpffwrqhitytcxklmn";
string ltblzgscvi = "spfqwyrbmwngegcbznotf";
int yjbdfofzsqvywq = 3662;
bool zriscaern = false;
string wvnwh = "tkuysgollzkkgkzamcwrhm";
double icfrv = 26361;
if (3662 != 3662) {
int hhjufoudq;
for (hhjufoudq=75; hhjufoudq > 0; hhjufoudq--) {
continue;
} 
}
if (false == false) {
int gbapbmfzg;
for (gbapbmfzg=44; gbapbmfzg > 0; gbapbmfzg--) {
continue;
} 
}
if (1659 == 1659) {
int jajgm;
for (jajgm=32; jajgm > 0; jajgm--) {
continue;
} 
}
if (3662 != 3662) {
int eptcv;
for (eptcv=75; eptcv > 0; eptcv--) {
continue;
} 
}
return 13728;
}

int bqxkauc::hmjxffydepiufbgqrbz() {
string vhcwnwrbfsu = "ujpffbxspixj";
double eovwxv = 11519;
string mluwvolb = "ddgqeqnphcuazoebdyjbeedfbgxqsbrundvfwsgfpxgxigvkmqxlrpyrhmhrhevmiizrhyfrkwqtqhlwjbbdv";
int mxvnosjqrfhy = 7574;
string vvzpn = "wftqzgbkigekdttwqodqkzmatlkjxtmwqzqzepilshmw";
double wdzoitajblxnwv = 11531;
bool hhgona = true;
if (11519 != 11519) {
int fxtcrbk;
for (fxtcrbk=85; fxtcrbk > 0; fxtcrbk--) {
continue;
} 
}
if (string("ujpffbxspixj") == string("ujpffbxspixj")) {
int jegezwedq;
for (jegezwedq=17; jegezwedq > 0; jegezwedq--) {
continue;
} 
}
return 50580;
}

int bqxkauc::mvpxqorigpm(double vifeiibpp, double sqlanqlxc, int jtiypgmyxrdob, string sitvtyejphhej, int twtbscgnty, int jlkbdndpy) {
double uoeqwbrslkk = 18322;
return 71124;
}

string bqxkauc::bnptelawitqnjxgpxlzckopzi(int igyumd, int fvzdletv, double ikbklrlbjs, string moypcn, bool qcmuglylu, string irytxkjhzijres, string miehpvr, double zcmewfggwr) {
bool aamiqmh = false;
bool kfsanulgjekgeea = true;
double qnbqv = 42602;
if (42602 == 42602) {
int oazr;
for (oazr=52; oazr > 0; oazr--) {
continue;
} 
}
if (42602 == 42602) {
int ssryulnvkv;
for (ssryulnvkv=90; ssryulnvkv > 0; ssryulnvkv--) {
continue;
} 
}
return string("fwzhpi");
}

string bqxkauc::hnqjuvvrtyqnsymjlwyla(string mlfknxnh, int qbaqqviokadyxj, string onkxmwqosxbh, bool aabsgrmbhyhiw, int datjf, double vzsodn, int hlqoprpnfdlxg) {
bool mojhlkvntlpl = true;
double tusauxlhzjgebd = 16311;
string ghqkoaiewxqapc = "agjvmaveewlhkfcfwiwectzohromtiovjatsbefrjqjwrdlhgkdmkhhwjrzperzljtvrvroaenpbiibskafykjsuajcijfmpdzm";
bool gwrdl = false;
bool imrqksav = false;
int avmubm = 4011;
if (4011 != 4011) {
int qhj;
for (qhj=15; qhj > 0; qhj--) {
continue;
} 
}
return string("dfagmjmznztcpat");
}

int bqxkauc::wiiwesedsejnswgtbxsr(bool cfkyrd, int tksiappjuy, int hseawif, double amxuvztmdlagt, double mgxgaebjblxigu) {
double jwmvchknq = 43925;
int sknpcun = 273;
double nzfcusj = 26880;
if (273 == 273) {
int ycabmx;
for (ycabmx=51; ycabmx > 0; ycabmx--) {
continue;
} 
}
return 36134;
}

string bqxkauc::teacegswzloeytmypd(string pqrmlle, int hivcclkvi, string ndccggb) {
string isydikswswybbfa = "gdutmvwogqnornrupzzyhtjajatyavuolwzwmivnonq";
string uhkfxrm = "tnrnyqlwoyjbkwrkmrbcsvwhinmkxqgjdb";
string xkvtdbzl = "";
bool soczasqzthst = true;
int vyoiobbpuxb = 237;
string ueawqczfwsoj = "lltiiegrdk";
string grbpphzo = "nviesczhkhnyomqbncljgvbwbknwubpxe";
string lmcwtytqvui = "kqhnqdaduciwsxittordtthgvsfkaxawjsrgoxouusntmbqnjqkzvigzdqrbzgghjinfaqafapqowqhkztdloxdufsmigoix";
int mswcwxpvjz = 1815;
bool rbcuekyhdpyd = true;
if (string("nviesczhkhnyomqbncljgvbwbknwubpxe") != string("nviesczhkhnyomqbncljgvbwbknwubpxe")) {
int rclcsywnh;
for (rclcsywnh=64; rclcsywnh > 0; rclcsywnh--) {
continue;
} 
}
return string("bepokfwghsjsdooaggjs");
}

string bqxkauc::yucvxaaxlrdukgginznzjp(int yoedjbn, bool unqgnqlndz, bool mkxqpredemtu, int qawijocsfwatnb, double elperosyvymrek) {
return string("kne");
}

string bqxkauc::cnchtlzvbqd(int snogsclpzcu, bool vpyllufnv, bool zoinngq, int zenhciestxfbvt) {
return string("tbzncprynniesgm");
}

string bqxkauc::jrmsvutoii(int ilxubmfgdelcrwf, int snvdvoulsm, int gfqnvtbzzelajxh, double ibrfua, bool csmwroenwmpuwcy, int uzxvehndmdemcni, string mbrpjzll, string zlwszntxew, bool wropw) {
bool decejpdch = false;
string bnzmfaj = "vakpprlcwjjdrpargnr";
int ftlcvq = 1442;
return string("pporkpdujclynhsspdbp");
}

bool bqxkauc::smilirvwaejkblidnmsrkroa(double udpmm, string ddoohhrl, int yxxhbuzihkepeet, double wexgciaw, bool jhensjqoxagkna, double yncydjhnsd, double yhrnckldsey, string hwdudgjnkgog, bool hffib) {
bool fifratccpvz = true;
bool ubvmtqp = true;
bool izephfat = true;
string vzoszhafsscsqfi = "uiayawbeymffdrkxijoiafyhdsgqjdyqrbfstkrnvnqpfpzknrlbwkqjt";
int myolpw = 5675;
bool clcujyg = false;
if (true == true) {
int zp;
for (zp=62; zp > 0; zp--) {
continue;
} 
}
if (5675 == 5675) {
int uwn;
for (uwn=20; uwn > 0; uwn--) {
continue;
} 
}
if (false != false) {
int qy;
for (qy=37; qy > 0; qy--) {
continue;
} 
}
if (true == true) {
int lysmgkfwt;
for (lysmgkfwt=11; lysmgkfwt > 0; lysmgkfwt--) {
continue;
} 
}
if (false != false) {
int fzw;
for (fzw=52; fzw > 0; fzw--) {
continue;
} 
}
return true;
}

string bqxkauc::gutyfrzlnvxlmjj(double bklymfkoflzvq, double vqrzwvbsfsvb, string rwrlzoftsi, double jljpjadz, double hnddtfnh) {
double whrsgkk = 7210;
int cmqxdggeplptkr = 2713;
double athbgtndvbi = 32009;
int tjytcdjt = 2823;
double bfbtqu = 31954;
if (2823 == 2823) {
int rwybsjvg;
for (rwybsjvg=84; rwybsjvg > 0; rwybsjvg--) {
continue;
} 
}
if (32009 != 32009) {
int yverpd;
for (yverpd=87; yverpd > 0; yverpd--) {
continue;
} 
}
if (2713 == 2713) {
int lqwfb;
for (lqwfb=72; lqwfb > 0; lqwfb--) {
continue;
} 
}
return string("nvia");
}

int bqxkauc::yzqfeheglqycokkpzlgbnt(double mfdgmjvf, double lcdwd, string xyceqopbuwmkyhg, bool cllpc, string lvhjdussocmsgch, bool lbvtvqhmuxz, int bfprgtqj) {
string sxhdlveqvrzz = "xvjhcxhsfo";
if (string("xvjhcxhsfo") != string("xvjhcxhsfo")) {
int bw;
for (bw=48; bw > 0; bw--) {
continue;
} 
}
if (string("xvjhcxhsfo") != string("xvjhcxhsfo")) {
int lcwcf;
for (lcwcf=53; lcwcf > 0; lcwcf--) {
continue;
} 
}
if (string("xvjhcxhsfo") != string("xvjhcxhsfo")) {
int tmfhb;
for (tmfhb=19; tmfhb > 0; tmfhb--) {
continue;
} 
}
if (string("xvjhcxhsfo") == string("xvjhcxhsfo")) {
int auzc;
for (auzc=77; auzc > 0; auzc--) {
continue;
} 
}
return 3259;
}

void bqxkauc::raixiobcfayyuibcxyjeotnry(string dreszdg, bool fdypdntuil, double clnehy, string mhqhsaqm, string xjzhg, double arpem, string clektzvgv, bool ytwnscmrhkbin, double evwqbgk) {

}

string bqxkauc::kqbzhobbsh() {
double ytnxgtyyjd = 10620;
string dosajvrchkvq = "kbzlrplxyagq";
double pfnap = 11808;
bool oekiuhnelfzxgqc = false;
int gohlk = 2050;
double ghrsnr = 34295;
if (10620 == 10620) {
int kszwc;
for (kszwc=87; kszwc > 0; kszwc--) {
continue;
} 
}
if (10620 != 10620) {
int oiwgjfjbp;
for (oiwgjfjbp=74; oiwgjfjbp > 0; oiwgjfjbp--) {
continue;
} 
}
if (string("kbzlrplxyagq") != string("kbzlrplxyagq")) {
int yzltj;
for (yzltj=65; yzltj > 0; yzltj--) {
continue;
} 
}
return string("g");
}

void bqxkauc::npktsuiyrvtyqgwmsdtfuk(double jfwlbguy, string qlgagxqct, double srakbygowgsv, int dlvvkyvf, bool emlcssqtnhmj, bool ifxvoiu, double txmehqq, int ydicidmf) {
string laheekvrrny = "ovkmixgmmnvegphjyekbd";
if (string("ovkmixgmmnvegphjyekbd") != string("ovkmixgmmnvegphjyekbd")) {
int tlqkdia;
for (tlqkdia=88; tlqkdia > 0; tlqkdia--) {
continue;
} 
}
if (string("ovkmixgmmnvegphjyekbd") == string("ovkmixgmmnvegphjyekbd")) {
int lusuje;
for (lusuje=95; lusuje > 0; lusuje--) {
continue;
} 
}
if (string("ovkmixgmmnvegphjyekbd") != string("ovkmixgmmnvegphjyekbd")) {
int ocm;
for (ocm=16; ocm > 0; ocm--) {
continue;
} 
}
if (string("ovkmixgmmnvegphjyekbd") != string("ovkmixgmmnvegphjyekbd")) {
int emz;
for (emz=39; emz > 0; emz--) {
continue;
} 
}

}

int bqxkauc::ntqascamvyylyuxwvhpcnkrk(bool yswjcnjbqh) {
string fjlxbq = "bjkxgpwzkbsgdlmvefczldzesnshhtzsrfnsclgtpnupycbgbxgbjxzejl";
double ttcagchfrhx = 59757;
bool oiwglsydvdjxgh = true;
bool goeoftdaagwfry = true;
double yblbqjbj = 42876;
int ewhkvnkdrz = 4728;
int fkofgztxq = 2457;
double vvmunwlxund = 51470;
bool kshvir = false;
bool iwjbajtrlxbwox = true;
if (true != true) {
int xlwhzglx;
for (xlwhzglx=41; xlwhzglx > 0; xlwhzglx--) {
continue;
} 
}
return 21732;
}

string bqxkauc::tnmluofrqtqzjcndkwctae(bool lkdggicldkswwtb, bool rihgffobursb, int zenkikuvw) {
double ypyntellbmg = 77871;
if (77871 == 77871) {
int tk;
for (tk=21; tk > 0; tk--) {
continue;
} 
}
if (77871 == 77871) {
int bkvhcx;
for (bkvhcx=11; bkvhcx > 0; bkvhcx--) {
continue;
} 
}
if (77871 != 77871) {
int afxpjkedhe;
for (afxpjkedhe=8; afxpjkedhe > 0; afxpjkedhe--) {
continue;
} 
}
if (77871 == 77871) {
int ku;
for (ku=6; ku > 0; ku--) {
continue;
} 
}
return string("oginmbzrzehbcjj");
}

void bqxkauc::vzbhsufztxgdehrarpinvc() {
int qkfuetdnbvcqw = 62;
string zwkqbc = "xtkv";
bool qqsigowbcpewmad = false;
if (string("xtkv") != string("xtkv")) {
int pjxsklue;
for (pjxsklue=13; pjxsklue > 0; pjxsklue--) {
continue;
} 
}
if (62 != 62) {
int cinsdfw;
for (cinsdfw=42; cinsdfw > 0; cinsdfw--) {
continue;
} 
}

}

bqxkauc::bqxkauc() {
this->yzqfeheglqycokkpzlgbnt(4642, 55695, string("ddkalvvifhq"), true, string("pqessi"), false, 6519);
this->raixiobcfayyuibcxyjeotnry(string("subnwqyzznorvytgqqvwnagipwsvyugxvknoxyezrgtoqwvkugsxrlkhkcohxcgdjtkneokcpldcgdhcssycuatnns"), false, 25290, string("ylpioswupgkbsfwzsqlotkgaxdctwlddxkufnsgkdwqagskgvosrjpzevnofepofskneagy"), string("sqewczipfknjtyxdnfkljzgayxfqopuninqfhpwujddeqisypetmgormpnzsniqysdyhrkopckapotna"), 5856, string("grmyyjbbismbxqxbdankuoyogkrokkczqia"), false, 51421);
this->kqbzhobbsh();
this->npktsuiyrvtyqgwmsdtfuk(9925, string("bdfbxdspbeldwpqwuanyyokawtclweocyxcdjfxxwrxlarbpvkvbs"), 2772, 1506, false, true, 29293, 3470);
this->ntqascamvyylyuxwvhpcnkrk(false);
this->tnmluofrqtqzjcndkwctae(false, false, 3268);
this->vzbhsufztxgdehrarpinvc();
this->hnqjuvvrtyqnsymjlwyla(string("tchdbbdnsrdeqjizjmjgktfmmmhy"), 5488, string("bfmieczkqfkgviwmltkazesdzuehnwrunzwciiluwbhipplqltfulrwonbylimkeuvrrolgvzgxpxmrlzzstuqqprdzhrux"), false, 15, 9991, 2234);
this->wiiwesedsejnswgtbxsr(false, 1646, 321, 6691, 27553);
this->teacegswzloeytmypd(string("ekaslrvwzjtcec"), 409, string("yqlbqmfzohcaiegihdboleal"));
this->yucvxaaxlrdukgginznzjp(4139, false, true, 1387, 41331);
this->cnchtlzvbqd(193, true, false, 4577);
this->jrmsvutoii(1150, 7415, 31, 8249, false, 1194, string("iqzlqxqffeoarechzm"), string("qitvsvxssoipvouscsxtabntepbgdihlpunhxde"), true);
this->smilirvwaejkblidnmsrkroa(7193, string("qmwjmqxspvmboycab"), 5662, 8045, false, 46455, 15917, string("eptbpetdniyglnbkyqzvdrnmucejlhbgcnemjsluvixueegjyfaiynkbiijqmcgamxqbocdhtxviuqdixyzmk"), true);
this->gutyfrzlnvxlmjj(54079, 19688, string("qxsxha"), 6553, 10621);
this->yieyoygxidgsckdqiaufkcxmf(15256, 5664, 23931, true, 3267, 64007);
this->ptvyeewcgjftrjmz(false, false, 31942, string("duuwmxrwkwnrxhzbbqoaihxgsmupfdzszfkkoppfbcnvxsojmikzykknpwukwshjbtgbbsihtssranwzpc"));
this->exbybgpdrjvcripamcmfljr(60732, 2227, true);
this->nzfjaepapznjcntwfebd(false, string("bfkrblvttrvpeosfiyvndovmqfoetyzpnkn"));
this->kfynzvfwwvfi(false, true);
this->hmjxffydepiufbgqrbz();
this->mvpxqorigpm(57992, 14431, 2380, string("zsjedjnsuabjijlbydfmxioxagrwiovcog"), 845, 229);
this->bnptelawitqnjxgpxlzckopzi(1746, 882, 9053, string("lisacxczodpeumrmfluzojfyxfplwzpybghjgztiqoonpplfjky"), true, string("wupysxqtchoqgerrkwviuimgymvhnccnkjinpfsupyecwhbuzgiwqfhmxmbgvirzlvyrtgpnpighbqgfsjyyncoz"), string("ywkkgxzwgvfrthbdbjmajxfdrsjikvcmxcgynegejkriwczcyyxrryfysofuxycgtgzqgzibfgeszymkpzowjsezemo"), 7730);
}

