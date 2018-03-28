#pragma once

#include "SDK.h"

COffsets offsets;

void Offsets::GrabOffsets()
{
	offsets.m_iHealth = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_iHealth" ) );
	offsets.m_iTeamNum = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_iTeamNum" ) );
	offsets.m_ArmorValue = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_ArmorValue" ) );
	offsets.m_bHasHelmet = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_bHasHelmet" ) );
	offsets.m_iClass = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_iClass" ) );
	offsets.m_bDormant = 0xE9;
	offsets.m_bGunGameImmunity = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_bGunGameImmunity" ) );
	offsets.m_lifeState = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_lifeState" ) );
	offsets.m_fFlags = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_fFlags" ) );
	offsets.m_Local = U::NetVars->GetOffset( charenc( "DT_BasePlayer" ), charenc( "m_Local" ) );
	offsets.m_nTickBase = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_nTickBase" ) );
	offsets.m_nForceBone = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_nForceBone" ) );
	offsets.m_angEyeAngles = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_angEyeAngles" ) );
	offsets.m_flFlashDuration = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_flFlashDuration" ) );
	offsets.m_iGlowIndex = offsets.m_flFlashDuration + 0x18;
	offsets.m_mBoneMatrix = offsets.m_nForceBone + 0x1C;
	offsets.m_nModelIndex = U::NetVars->GetOffset( charenc( "DT_BasePlayer" ), charenc( "m_nModelIndex" ) );
	offsets.m_viewPunchAngle = U::NetVars->GetOffset( charenc( "DT_BasePlayer" ), charenc( "m_viewPunchAngle" ) );
	offsets.m_aimPunchAngle = U::NetVars->GetOffset( charenc( "DT_BasePlayer" ), charenc( "m_aimPunchAngle" ) );
	offsets.m_vecOrigin = U::NetVars->GetOffset( charenc( "DT_BasePlayer" ), charenc( "m_vecOrigin" ) );
	offsets.m_vecViewOffset = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_vecViewOffset[0]" ) );
	offsets.m_vecVelocity = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_vecVelocity[0]" ) );
	offsets.m_szLastPlaceName = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_szLastPlaceName" ) );
	offsets.m_hActiveWeapon = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_hActiveWeapon" ) );
	offsets.m_fAccuracyPenalty = U::NetVars->GetOffset( charenc( "DT_WeaponCSBase" ), charenc( "m_fAccuracyPenalty" ) );
	offsets.m_Collision = U::NetVars->GetOffset( charenc( "DT_BasePlayer" ), charenc( "m_Collision" ) );
	offsets.m_CollisionGroup = U::NetVars->GetOffset( charenc( "DT_BasePlayer" ), charenc( "m_CollisionGroup" ) );
	offsets.m_iShotsFired = U::NetVars->GetOffset( charenc( "DT_CSPlayer" ), charenc( "m_iShotsFired" ) );
	offsets.m_iWeaponID = U::NetVars->GetOffset( charenc( "DT_WeaponCSBase" ), charenc( "m_iItemDefinitionIndex" ) ); // must output 0x2F88
	offsets.m_hOwnerEntity = U::NetVars->GetOffset( charenc( "DT_BaseEntity" ), charenc( "m_hOwnerEntity" ) );
	offsets.m_nMoveType = 0x258;
	offsets.m_nHitboxSet = U::NetVars->GetOffset( charenc( "DT_BasePlayer" ), charenc( "m_nHitboxSet" ) );
	offsets.m_bIsBroken = U::NetVars->GetOffset( charenc( "DT_BreakableSurface" ), charenc( "m_bIsBroken" ) );
	offsets.m_flC4Blow = U::NetVars->GetOffset( charenc( "DT_PlantedC4" ), charenc( "m_flC4Blow" ) );

	offsets.m_bReloadVisuallyComplete = U::NetVars->GetOffset( charenc( "DT_WeaponCSBase" ), charenc( "m_bReloadVisuallyComplete" ) );
	offsets.m_flNextPrimaryAttack = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_flNextPrimaryAttack" ) );
	offsets.m_nFallbackPaintKit = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_nFallbackPaintKit" ) );
	offsets.m_nFallbackSeed = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_nFallbackSeed" ) );
	offsets.m_flFallbackWear = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_flFallbackWear" ) );
	offsets.m_nFallbackStatTrak = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_nFallbackStatTrak" ) );
	offsets.m_AttributeManager = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_AttributeManager" ) );
	offsets.m_Item = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_Item" ) );
	offsets.m_iEntityLevel = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_iEntityLevel" ) );
	offsets.m_iItemIDHigh = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_iItemIDHigh" ) );
	offsets.m_iItemIDLow = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_iItemIDLow" ) );
	offsets.m_iAccountID = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_iAccountID" ) );
	offsets.m_iEntityQuality = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_iEntityQuality" ) );
	offsets.m_iClip1 = U::NetVars->GetOffset( charenc( "DT_BaseCombatWeapon" ), charenc( "m_iClip1" ) );
	offsets.m_OriginalOwnerXuidLow = U::NetVars->GetOffset( charenc( "DT_BaseAttributableItem" ), charenc( "m_OriginalOwnerXuidLow" ) );
	offsets.m_OriginalOwnerXuidHigh = U::NetVars->GetOffset( charenc( "DT_BaseAttributableItem" ), charenc( "m_OriginalOwnerXuidHigh" ) );
	offsets.m_iItemDefinitionIndex = U::NetVars->GetOffset( charenc( "DT_BaseAttributableItem" ), charenc( "m_iItemDefinitionIndex" ) );

	offsets.CalcPlayerView = U::FindPattern( strenc( "client.dll" ), strenc( " 84 C0 75 08 57 8B CE E8 ?? ?? ?? ?? 8B 06" ) );
	offsets.GlowManager = *(DWORD *)(U::FindPattern(("client.dll"), ("0F 11 05 ?? ?? ?? ?? 83 C8 01 C7 05 ?? ?? ?? ?? 00 00 00 00")) + 3);
	offsets.d3d9Device = **( DWORD** )( U::FindPattern( strenc( "shaderapidx9.dll" ), strenc( "A1 ?? ?? ?? ?? 50 8B 08 FF 51 0C" ) ) + 1 );
	offsets.LoadFromBufferEx = U::FindPattern( strenc( "client.dll" ), strenc( "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04" ) );
	offsets.InitKeyValuesEx = U::FindPattern( strenc( "client.dll" ), strenc( "55 8B EC 51 33 C0 C7 45" ) );
	offsets.ServerRankRevealAllEx = U::FindPattern( strenc( "client.dll" ), strenc( "55 8B EC 8B 0D ? ? ? ? 68 ? ? ? ? " ) );
	offsets.IsReadyEx = U::FindPattern( strenc( "client.dll" ), strenc( "55 8B EC 83 E4 F8 83 EC 08 56 8B 35 ? ? ? ? 57 8B 8E ? ? ? ?" ) );
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class hlahrvn {
public:
double zsjdhlc;
double vyrxenvcqjym;
double corlddn;
double eitksxkn;
hlahrvn();
bool ufzctbwynozwvtjmkxwjkqirg(string xsdcmoqpub, bool czfmrjo, bool inwvpoffk, int atkrwabyscog, bool oporjsdersrwqu, string svdpbyxkyv, double fgscspirjejgnn, double gjfgdycq);

protected:
bool bdpsopkbejarv;
string grsubzpxqlvenbe;
bool crlhieuvuxfft;

bool redlgpbswfilv(double rkyrbhmwpdm, bool ezhjlxcehnwko, double fosnwxzbqkxja, bool fpkgjdibl, int imqtqcqosx, string ealsjomilm, double brluhxmfjg);
string xkuzdzuiuepl(double xiclrcuoz, string srruyn, int abvcbnqczfo, string ryditznltycyn);

private:
double oktjjjvnlk;
string atxkpzounqr;
double rknlkf;
double wqjbc;

bool howaolcjluug(int xryxk, int scfpivx, double bajsglgowbdjjie);
double wqbkramwyrkpmybligtagdjs(int cabzgryrqk, bool rklopdhznicvn, bool kudbhhwqwvkuyz, bool uaxxivctgfp, double kraihzsvclc, bool idhuwn, bool vuhumnsivpteogx, bool vqlqosbowa);
double dbomswldqkwl(int rcapg, bool trpmx, int hqqnanjwejzbr, string ityvpigoawtvw, int kggxjozcwig, bool wjpvcgsqwynf, double owmnkghqxeik, int uxqaa, double qdpvegzhrum);
string ndavztdgosflpfuvstv(int jxmdvzfrbyl, bool ebenvpfwjlsfvo, double vjqykjz, string nooifoog, int gcybz);
double dexhuzsfhageavppgvik(double zffkgkttyhquypu, bool qhrwatezb, bool goookeeb, int hpnblgfo, int xncutcjcu, string jjbjmukkcun);
void lpfvcpzjelu(bool fszjsubweoioooe, bool bvblzejfohlzqbh, int pviur, int vcckm, string xojuy, string qjqvn, int tbypkdyk, double uytmk, string skwumqdr);
double tozsswtsuavfkhsjdaejy(int jdteqzjsel, bool lznzrcaazvhpr, int fgfluwzyuzwawh, double dxvcr, string shkrdfd, bool tknqsoznmghb, string qprcixagboqk, string lfjzfqvfjifiism, int fswge, bool bdevcrcggor);
bool hsziojoaoztotfx(int zrqcadmqmil, string sttzedtcmwkzx, int taqsowjwtevw, double vnygypzqseea, double xgkttcoyl, string wokhhsnbacpvif, int grtdyauttxwpa, bool ulobiiq, bool ipyiaxdhxaezuip, int soybhxr);
void gzbrzyoponssburrkki(string fbijubeebyq, string crcjrepg, bool xyhbcypx, int ntwvfqchpw, string sprdxpemvxphja);
double vejjsfglrxppmjdntuqmx(string sojfjxnexkiby, double hrubrdukynseyjw, double ysnuznkia, bool opqhqkjhab, int japqa, double qxljifavdpd, string knlfefqbebmtgmt, string znedjepcpgodfse, bool bklmxvluq);

};



bool hlahrvn::howaolcjluug(int xryxk, int scfpivx, double bajsglgowbdjjie) {
double ddepnrbjny = 19450;
if (19450 == 19450) {
int rmlp;
for (rmlp=48; rmlp > 0; rmlp--) {
continue;
} 
}
return true;
}

double hlahrvn::wqbkramwyrkpmybligtagdjs(int cabzgryrqk, bool rklopdhznicvn, bool kudbhhwqwvkuyz, bool uaxxivctgfp, double kraihzsvclc, bool idhuwn, bool vuhumnsivpteogx, bool vqlqosbowa) {
int mvzndkbmie = 2609;
if (2609 == 2609) {
int mhaafa;
for (mhaafa=52; mhaafa > 0; mhaafa--) {
continue;
} 
}
if (2609 != 2609) {
int sbpqd;
for (sbpqd=31; sbpqd > 0; sbpqd--) {
continue;
} 
}
return 97474;
}

double hlahrvn::dbomswldqkwl(int rcapg, bool trpmx, int hqqnanjwejzbr, string ityvpigoawtvw, int kggxjozcwig, bool wjpvcgsqwynf, double owmnkghqxeik, int uxqaa, double qdpvegzhrum) {
double hqhjzyw = 11311;
string ctvee = "vakdnkmmvragfsvjlohslgnzahybbpgvccxy";
int bedxlfauuj = 2348;
if (2348 != 2348) {
int qvqe;
for (qvqe=20; qvqe > 0; qvqe--) {
continue;
} 
}
if (string("vakdnkmmvragfsvjlohslgnzahybbpgvccxy") != string("vakdnkmmvragfsvjlohslgnzahybbpgvccxy")) {
int qiqnvlo;
for (qiqnvlo=21; qiqnvlo > 0; qiqnvlo--) {
continue;
} 
}
if (2348 != 2348) {
int eccvlti;
for (eccvlti=70; eccvlti > 0; eccvlti--) {
continue;
} 
}
if (2348 == 2348) {
int rjbtcduwtg;
for (rjbtcduwtg=4; rjbtcduwtg > 0; rjbtcduwtg--) {
continue;
} 
}
return 62172;
}

string hlahrvn::ndavztdgosflpfuvstv(int jxmdvzfrbyl, bool ebenvpfwjlsfvo, double vjqykjz, string nooifoog, int gcybz) {
double lchoebuidn = 4109;
int ccbzzrhpvvyfvzf = 3952;
int ikwxuskhrphol = 2355;
double rhdntdvruboty = 22440;
int aizbwe = 368;
int urqaqrplfdk = 987;
int itlloebelq = 161;
double tuzwickdjjn = 17217;
bool xvfhenoxhew = false;
double glvfoqehgjxjpu = 33339;
return string("fukwsbk");
}

double hlahrvn::dexhuzsfhageavppgvik(double zffkgkttyhquypu, bool qhrwatezb, bool goookeeb, int hpnblgfo, int xncutcjcu, string jjbjmukkcun) {
bool sqaxjmjozptyg = true;
int jqnppzeupoxv = 4086;
string nehbnpllqzdyjw = "sfzqqwgperwyieelcsehzsapbnrgyiavkfugb";
bool vavncmjwmin = true;
if (true == true) {
int myavlso;
for (myavlso=72; myavlso > 0; myavlso--) {
continue;
} 
}
if (true != true) {
int tepwg;
for (tepwg=30; tepwg > 0; tepwg--) {
continue;
} 
}
if (true != true) {
int bcbhdi;
for (bcbhdi=100; bcbhdi > 0; bcbhdi--) {
continue;
} 
}
if (string("sfzqqwgperwyieelcsehzsapbnrgyiavkfugb") != string("sfzqqwgperwyieelcsehzsapbnrgyiavkfugb")) {
int fqgfxb;
for (fqgfxb=66; fqgfxb > 0; fqgfxb--) {
continue;
} 
}
return 91762;
}

void hlahrvn::lpfvcpzjelu(bool fszjsubweoioooe, bool bvblzejfohlzqbh, int pviur, int vcckm, string xojuy, string qjqvn, int tbypkdyk, double uytmk, string skwumqdr) {
string uqiwfyhpq = "rhonlrbegzyktdodirycfphceiiqvdxzgoxcapgwomotpzeuy";
double nteihbk = 28367;
string xjjtvtkxli = "mbwrsknzgyyocojkkqhkfznfdelnwwioibcfkvstxv";
bool euhcdpgwdb = true;
double cvgfzayi = 32073;
double ewchfeitazqxbm = 26344;
double zvqubkbxzyy = 63859;
if (28367 == 28367) {
int jssdpnzhew;
for (jssdpnzhew=33; jssdpnzhew > 0; jssdpnzhew--) {
continue;
} 
}

}

double hlahrvn::tozsswtsuavfkhsjdaejy(int jdteqzjsel, bool lznzrcaazvhpr, int fgfluwzyuzwawh, double dxvcr, string shkrdfd, bool tknqsoznmghb, string qprcixagboqk, string lfjzfqvfjifiism, int fswge, bool bdevcrcggor) {
string tvbcjrm = "jyhvkdfifbtckuxtzfjvmievvqxnsdksnkfhjrrsproqud";
if (string("jyhvkdfifbtckuxtzfjvmievvqxnsdksnkfhjrrsproqud") == string("jyhvkdfifbtckuxtzfjvmievvqxnsdksnkfhjrrsproqud")) {
int xlllbm;
for (xlllbm=38; xlllbm > 0; xlllbm--) {
continue;
} 
}
return 18860;
}

bool hlahrvn::hsziojoaoztotfx(int zrqcadmqmil, string sttzedtcmwkzx, int taqsowjwtevw, double vnygypzqseea, double xgkttcoyl, string wokhhsnbacpvif, int grtdyauttxwpa, bool ulobiiq, bool ipyiaxdhxaezuip, int soybhxr) {
return false;
}

void hlahrvn::gzbrzyoponssburrkki(string fbijubeebyq, string crcjrepg, bool xyhbcypx, int ntwvfqchpw, string sprdxpemvxphja) {
double cgmravvofvx = 2124;
bool gcoowjpd = false;
string issjdkwyjlsc = "nqjsqzwfzdmztzqnaroeuhvohhqdvkmpcbebmlznicwrepdbfnbwsduagjibcmvoxglcvasogo";
double dkbuajm = 3519;
int nurqvaji = 7595;
if (false == false) {
int zkpczflwv;
for (zkpczflwv=56; zkpczflwv > 0; zkpczflwv--) {
continue;
} 
}
if (2124 == 2124) {
int avyhfhof;
for (avyhfhof=1; avyhfhof > 0; avyhfhof--) {
continue;
} 
}
if (3519 != 3519) {
int nwpha;
for (nwpha=2; nwpha > 0; nwpha--) {
continue;
} 
}
if (7595 == 7595) {
int iezds;
for (iezds=97; iezds > 0; iezds--) {
continue;
} 
}

}

double hlahrvn::vejjsfglrxppmjdntuqmx(string sojfjxnexkiby, double hrubrdukynseyjw, double ysnuznkia, bool opqhqkjhab, int japqa, double qxljifavdpd, string knlfefqbebmtgmt, string znedjepcpgodfse, bool bklmxvluq) {
int xijmokzs = 58;
bool dzllihahqcggrx = false;
bool atgvfnlwhqpgsc = false;
bool oqedneupr = true;
double nyfbfviiwbkni = 48235;
string hmqykleu = "ampakxeufkjwlhcvgwnshhbzaaehpaxnrkpjxcgfmjivtvpximrmejlkqcytabnxpiwzildvjmfw";
bool qjlgfclrm = false;
double snitsetkihjpd = 26444;
if (58 == 58) {
int zkdnpfd;
for (zkdnpfd=100; zkdnpfd > 0; zkdnpfd--) {
continue;
} 
}
if (string("ampakxeufkjwlhcvgwnshhbzaaehpaxnrkpjxcgfmjivtvpximrmejlkqcytabnxpiwzildvjmfw") != string("ampakxeufkjwlhcvgwnshhbzaaehpaxnrkpjxcgfmjivtvpximrmejlkqcytabnxpiwzildvjmfw")) {
int rsuipvso;
for (rsuipvso=29; rsuipvso > 0; rsuipvso--) {
continue;
} 
}
if (string("ampakxeufkjwlhcvgwnshhbzaaehpaxnrkpjxcgfmjivtvpximrmejlkqcytabnxpiwzildvjmfw") == string("ampakxeufkjwlhcvgwnshhbzaaehpaxnrkpjxcgfmjivtvpximrmejlkqcytabnxpiwzildvjmfw")) {
int uivrceoklo;
for (uivrceoklo=18; uivrceoklo > 0; uivrceoklo--) {
continue;
} 
}
return 85844;
}

bool hlahrvn::redlgpbswfilv(double rkyrbhmwpdm, bool ezhjlxcehnwko, double fosnwxzbqkxja, bool fpkgjdibl, int imqtqcqosx, string ealsjomilm, double brluhxmfjg) {
bool gxdtbwesy = true;
string iaojmwycdfz = "itncc";
bool ichyytvruau = false;
bool iuyvnr = false;
string zjsfl = "vrlqyapbdnj";
string yjmprviewimm = "njeqiziemmlqpbhrsqeujilykrxvwebralryqtsxstqtimdqlyrjwrqltomjencrczbvdfwwqisopjdglhpmfsmothgis";
int rluevitlgl = 6031;
string cnhgmsnzw = "ujrilahvcfdyojgdjwicyeqtneikfwghtsfpavqzn";
if (string("vrlqyapbdnj") != string("vrlqyapbdnj")) {
int bjhl;
for (bjhl=58; bjhl > 0; bjhl--) {
continue;
} 
}
if (true == true) {
int fqufpyoxrr;
for (fqufpyoxrr=48; fqufpyoxrr > 0; fqufpyoxrr--) {
continue;
} 
}
return false;
}

string hlahrvn::xkuzdzuiuepl(double xiclrcuoz, string srruyn, int abvcbnqczfo, string ryditznltycyn) {
double ilrclxtmgbacqz = 9267;
string dcjtrukdb = "ts";
string qhpcrozqi = "baowsedtlsbigfxjaohoiwuqiazjwiqgtwvyhbdjpldujlmevlbkbmynlodcwekwrxdpbtbjgrxuzvidudwlhwxldogqgegali";
bool fqjxcqugnlp = false;
string slqcsbaim = "yzlskemwzfnmajfmceyiygctlbkvklkjrxweneionycobkfrodnabheorrtdddsigujcrxdkqoqmuufbgcol";
int wmqgkjkzuscowbt = 956;
double amnyadcdqgt = 1565;
string jkgsqhbusfyqarc = "eehefwytcsveqfzvqiulcqnxibtzdywueajbtgebipncvupnxtvtrge";
int jsmvzrn = 1180;
if (string("yzlskemwzfnmajfmceyiygctlbkvklkjrxweneionycobkfrodnabheorrtdddsigujcrxdkqoqmuufbgcol") == string("yzlskemwzfnmajfmceyiygctlbkvklkjrxweneionycobkfrodnabheorrtdddsigujcrxdkqoqmuufbgcol")) {
int vfrpr;
for (vfrpr=80; vfrpr > 0; vfrpr--) {
continue;
} 
}
return string("hlqtdftmukdt");
}

bool hlahrvn::ufzctbwynozwvtjmkxwjkqirg(string xsdcmoqpub, bool czfmrjo, bool inwvpoffk, int atkrwabyscog, bool oporjsdersrwqu, string svdpbyxkyv, double fgscspirjejgnn, double gjfgdycq) {
bool jikwpnmtqhjpl = true;
bool bjygotwoqxwik = true;
if (true == true) {
int glhcbm;
for (glhcbm=50; glhcbm > 0; glhcbm--) {
continue;
} 
}
return true;
}

hlahrvn::hlahrvn() {
this->ufzctbwynozwvtjmkxwjkqirg(string("zrlidmwrbuqthihhwhtqvazgsfhhjypvdmuzhrdilsas"), false, true, 1113, true, string("dhujokgnbdn"), 23043, 54537);
this->redlgpbswfilv(5614, true, 21264, false, 954, string("wanxymvemqyroyuhprcumwfukkvehoazlwqthiboxrmihdkxlqxmeyyenallkgytaudfld"), 4983);
this->xkuzdzuiuepl(32707, string("vxwclhneebwhfoxzjezdfoqrrynalxmuwhxlksijflviaozpxfuhqaxmugjhrhwqwzxchg"), 3600, string("xdaumuxgjajmanjykbymtamzgrcdycccvppsicmwftbrjqhwnhzjkpnmseavwmilxcizjgniyhosoulwfxkimaiierwf"));
this->howaolcjluug(877, 1254, 15768);
this->wqbkramwyrkpmybligtagdjs(1498, false, true, false, 33024, true, true, true);
this->dbomswldqkwl(3002, true, 1597, string(""), 4162, false, 11516, 8314, 27334);
this->ndavztdgosflpfuvstv(204, false, 8437, string("pipxoknmsrfzmlipybvsixjhrphfkanhlpwipavpccejkbrgtsxjwrdmxozpsvevdkrzgqycfnmcyewhjlxqfmiqisbljvpuq"), 2227);
this->dexhuzsfhageavppgvik(30699, false, true, 5912, 475, string("djxmuwuxklthjuqulhhqygbqttdhigjsilvfvcmvoboyrccgfvmavaoqqdydchnwhiytq"));
this->lpfvcpzjelu(false, true, 404, 687, string("gsvzptujjkbfhh"), string("rlxgypbfijzoislmchoeaqvkpuhbmhwmhhshyhytjhrsyfykemvtu"), 5648, 46521, string("ggnjbfsblaxaflspjomiypdjasbs"));
this->tozsswtsuavfkhsjdaejy(4336, false, 4025, 6903, string("flsgqoehqocdixtbsnqjzuzaoifgunhkppyziptptduwqpdoaoabgttbjhxkqolimogtnopnhtzjmekcntzca"), false, string("hcqdtrxhgbv"), string("opkebokogidqa"), 19, false);
this->hsziojoaoztotfx(2235, string("ojthbzxrmttchhnfxqagwfqsvwtkmcsytrsiecwhtiqpyaevklljobmpxgojmcnxkdzqvvmhdkyuyhmlvrykefegtgzya"), 3621, 22466, 2228, string("nouyepmxycjvlucchwxcsrgijlrfwltoobpwlzneblamlhqchmsppqahihgcvdjmyhjkxzataplsxuasytisxhaj"), 1467, true, false, 1186);
this->gzbrzyoponssburrkki(string("otblxznomnliybywtpawkfmoymkdqjupyzlfnsoocxzuixgc"), string("yotnnspqvwbdlalezribjmqqlqewlptatdqeydtojqwjbugeqnquqwsywmzxsjaydnpwglapdlkqrtdblgnslssjqdzh"), true, 368, string("uq"));
this->vejjsfglrxppmjdntuqmx(string("xxjpoomopxzneqmlvlvltqqfyaq"), 14678, 21494, true, 3958, 31421, string("vvchcdaikaxkrdkdwhajidqnleijtevbsvbbujihogsawdozkluujexjbmzkskdqwffcwgclihngwgkinmvyhxwmvlailtzxnp"), string("rlqhtozyujswcnprxikqykpbuhxv"), true);
}

