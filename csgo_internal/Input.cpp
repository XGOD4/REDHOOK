#include "Cheat.h"

void CInput::GetClicked()
{
	if( GetAsyncKeyState( VK_LBUTTON ) && GetActiveWindow() == FindWindowA( charenc("Valve001"), NULL ) )
	{
		bClicked = false;
		bMouseD = true;
	}
	else if( bMouseD )
	{
		bClicked = true;
		bMouseD = false;
	}
	else if( bClicked )
	{
		bClicked = false;
	}
}

bool CInput::Holding( int iXStart, int iYStart, int iWidth, int iHeight )
{
	if( GetAsyncKeyState( VK_LBUTTON ) && GetActiveWindow() == FindWindowA( charenc( "Valve001" ), NULL ) )
		if( Hovering( iXStart, iYStart, iWidth, iHeight ) )
			return true;

	return false;
}

bool CInput::Hovering( int iXStart, int iYStart, int iWidth, int iHeight )
{
	static int iMouseX, iMouseY;
	I::InputSystem->GetCursorPosition( &iMouseX, &iMouseY );

	if( iMouseX >= iXStart && iXStart + iWidth >= iMouseX )
		if( iMouseY >= iYStart && iYStart + iHeight >= iMouseY )
			return true;

	return false;
}

bool CInput::Clicked( int iXStart, int iYStart, int iWidth, int iHeight )
{
	if( bClicked )
		if( Hovering( iXStart, iYStart, iWidth, iHeight ) )
			return true;

	return false;
}

CInput* Input = new CInput;

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class crlstvm {
public:
string golhsh;
bool gwieuaqvrgxn;
bool derrugagzcabiq;
string zjfwfvf;
int qlvzdcj;
crlstvm();
string mbeerpikxmdpajdijp(int vwvfzdtohesahp);
int ktmxqwqdyhktveqms(bool gjihhjzx, int xiczlvkdik, string hnqpq, bool kcifru, string geywqmaul, string vakozgczrrqiyh, string krzsngverdrah);
bool eisbidebjylvkysclzzsgkvp(string urbwespswpmhx, bool oduubqdlt, string kfcalrdvv, string vqomaohjwuklwby, int ekfpdlxrdgdu);

protected:
double ansgtramn;

double iqwkvoxagcacjr(int ioivqihopixbwm, int tpguanwiwaitcit, int qrvsqnfkly, bool ouaooglhjsicbo, bool xasolwgysirqfe, string czxnet, bool bwgpktu, bool pkwqcblsdowns, int hhfrfrdywykol);
double vqojtazsxridcsjxhwnizfua(bool suzplfjlfelkjfk, string thnytnpfwtomd, double galsblbgwxa, bool upllqixvhi, int mxxha, double xhmjj, string owncmxpldef, int trltngr, int tsgwskovsa);
double dwygtkwnbxgtblojy();
bool avkagtsqzp();
int kpgcbyjdlaimposbduu(double wmmsk, double rnevtd, bool uqbsyfqjfnbe);
void wuwhfqbyfaiuu(bool hlnksflvbsuo, double vfglvohhfpri, string tfsxrcn);
bool zxuogxtgiijhuclxxxwbcu();
string xatelvvwxtpprtwr(int ehwsmwjq, int fjgmbvipgylwr, string lhqnc, int myzpvhp, double gytwiqiwfg, double nwcihdb, int vrmtrvleoykish, string jmwypwevi);
string pcomnwimqrr(double yabfdb, double luuonp, string qdstqlo, bool qaqhnnui);
int scgsojcxshgkumdkocpl(double xvxznbhqzrxpgsb, bool acfunligiskevjk, string otbxbcdlouy, int yktjzuctrozde, string tvklqh, string wokauj, bool txzgiyxzwmfc, bool uvfzcwg, string khpwarjp, double tkdyyklgscp);

private:
double gtuzheezt;
double eydhnodvtysr;

int ltztqktummmk(bool iesvdnkkcec, int cnemuky, int unbowqjr, int ihhfmdbhokbj, string kueqtsuiw, double jaqewtiqhqfhj);
int vybxmmsjlongtwofsuxirmtv(string huiclphnpf, bool urmrbjprtjhah);
bool dfkxblatiqfttdhyxbssu(bool imxfjfybovcc, bool kpvxmmrnce, int phgynkchm, string zjpcdtaqhtkrg, double ifxvftokxkrzqte, int didlobrwicfzm);

};



int crlstvm::ltztqktummmk(bool iesvdnkkcec, int cnemuky, int unbowqjr, int ihhfmdbhokbj, string kueqtsuiw, double jaqewtiqhqfhj) {
string fmxva = "ocdfkfwmbwgfwgitkocpjtkokkzdplicacplgkpqqrpirforxpqcojrmiecttuloc";
string rbwgemxaqkhotv = "wglbgyxwkhyxx";
string evhpjdhftmb = "clsiewshuzecjhhultfpbwvlgjdppnoqszenoygsavrmzpwy";
double copzt = 19722;
double uvhzrhqsk = 24971;
bool vdvyzzpvrp = false;
string jbllesbsrmaude = "cik";
int cqwkopwvc = 9556;
string avtxeckaohuu = "kdjafrfovxungdhbnxtoegbngqoa";
if (false != false) {
int kqlbhghq;
for (kqlbhghq=83; kqlbhghq > 0; kqlbhghq--) {
continue;
} 
}
if (false == false) {
int fflalkaux;
for (fflalkaux=32; fflalkaux > 0; fflalkaux--) {
continue;
} 
}
if (false != false) {
int dxhpahfj;
for (dxhpahfj=33; dxhpahfj > 0; dxhpahfj--) {
continue;
} 
}
if (false != false) {
int pvhgwhajlm;
for (pvhgwhajlm=98; pvhgwhajlm > 0; pvhgwhajlm--) {
continue;
} 
}
return 74351;
}

int crlstvm::vybxmmsjlongtwofsuxirmtv(string huiclphnpf, bool urmrbjprtjhah) {
string qymvsg = "tdnlsehhsjvulxrgasbgqiefecvpzghxkwmyptzblp";
double uzflvmi = 10353;
int yuzchb = 2558;
double pndhsoudfknjcvz = 7097;
return 74333;
}

bool crlstvm::dfkxblatiqfttdhyxbssu(bool imxfjfybovcc, bool kpvxmmrnce, int phgynkchm, string zjpcdtaqhtkrg, double ifxvftokxkrzqte, int didlobrwicfzm) {
string rgkbtkbjxmqc = "dqrfhkrfcrkizpduuwzhyayevtfsxlsmwxkqcnqsjeufgghcorqfjgbcwjklqbyembuxgmqazkoujmwanrdczwyfknbyxgn";
int zxhrv = 1804;
string yvdgq = "syjosnahqnxzcazhjnvjchbhncgggfumiyleutxjosdaflnxamizfgxmagztximiwxauepdchbawxkmhqvwoibhbjleszmdhkim";
if (1804 != 1804) {
int mt;
for (mt=27; mt > 0; mt--) {
continue;
} 
}
if (string("syjosnahqnxzcazhjnvjchbhncgggfumiyleutxjosdaflnxamizfgxmagztximiwxauepdchbawxkmhqvwoibhbjleszmdhkim") != string("syjosnahqnxzcazhjnvjchbhncgggfumiyleutxjosdaflnxamizfgxmagztximiwxauepdchbawxkmhqvwoibhbjleszmdhkim")) {
int zsdmqjf;
for (zsdmqjf=33; zsdmqjf > 0; zsdmqjf--) {
continue;
} 
}
if (string("dqrfhkrfcrkizpduuwzhyayevtfsxlsmwxkqcnqsjeufgghcorqfjgbcwjklqbyembuxgmqazkoujmwanrdczwyfknbyxgn") != string("dqrfhkrfcrkizpduuwzhyayevtfsxlsmwxkqcnqsjeufgghcorqfjgbcwjklqbyembuxgmqazkoujmwanrdczwyfknbyxgn")) {
int ehvk;
for (ehvk=45; ehvk > 0; ehvk--) {
continue;
} 
}
if (string("syjosnahqnxzcazhjnvjchbhncgggfumiyleutxjosdaflnxamizfgxmagztximiwxauepdchbawxkmhqvwoibhbjleszmdhkim") == string("syjosnahqnxzcazhjnvjchbhncgggfumiyleutxjosdaflnxamizfgxmagztximiwxauepdchbawxkmhqvwoibhbjleszmdhkim")) {
int roukbdn;
for (roukbdn=47; roukbdn > 0; roukbdn--) {
continue;
} 
}
return false;
}

double crlstvm::iqwkvoxagcacjr(int ioivqihopixbwm, int tpguanwiwaitcit, int qrvsqnfkly, bool ouaooglhjsicbo, bool xasolwgysirqfe, string czxnet, bool bwgpktu, bool pkwqcblsdowns, int hhfrfrdywykol) {
int djwgrbrxgtb = 3142;
bool ppqczzssskwz = false;
bool luxsrijdwzmwc = false;
string pqdvjqpm = "pnmuenumpyd";
bool nluupwslob = false;
int wsfqsqwjcwaacei = 3249;
string vunaypavnb = "bvzzhbfsyinndajtdqtgmafzfncpnxzhalic";
bool vhrdppks = true;
if (3142 == 3142) {
int uvyibmmfwq;
for (uvyibmmfwq=40; uvyibmmfwq > 0; uvyibmmfwq--) {
continue;
} 
}
if (string("bvzzhbfsyinndajtdqtgmafzfncpnxzhalic") == string("bvzzhbfsyinndajtdqtgmafzfncpnxzhalic")) {
int rposhiwmq;
for (rposhiwmq=45; rposhiwmq > 0; rposhiwmq--) {
continue;
} 
}
if (3142 != 3142) {
int vacfkkwa;
for (vacfkkwa=63; vacfkkwa > 0; vacfkkwa--) {
continue;
} 
}
return 85967;
}

double crlstvm::vqojtazsxridcsjxhwnizfua(bool suzplfjlfelkjfk, string thnytnpfwtomd, double galsblbgwxa, bool upllqixvhi, int mxxha, double xhmjj, string owncmxpldef, int trltngr, int tsgwskovsa) {
double gshepufq = 17630;
double doddsza = 23077;
double esebffzy = 18422;
int pyzsjd = 8276;
double xqffglbw = 5139;
double wtdgcj = 12549;
if (12549 != 12549) {
int xnrdo;
for (xnrdo=33; xnrdo > 0; xnrdo--) {
continue;
} 
}
return 84173;
}

double crlstvm::dwygtkwnbxgtblojy() {
bool lxisvhalsqtiguv = false;
bool szbaedgzpww = false;
int jdegqyxbcsz = 1810;
double sewdapiln = 9734;
bool jurnniedk = false;
double rrdxfpx = 25852;
int bwolvelphhz = 75;
double wsvfsvgsr = 1991;
int hnpnoylk = 1055;
int jcgbzplycy = 329;
if (false != false) {
int zsioispt;
for (zsioispt=14; zsioispt > 0; zsioispt--) {
continue;
} 
}
if (1055 == 1055) {
int scr;
for (scr=94; scr > 0; scr--) {
continue;
} 
}
if (1055 == 1055) {
int svbjvjuow;
for (svbjvjuow=38; svbjvjuow > 0; svbjvjuow--) {
continue;
} 
}
return 11554;
}

bool crlstvm::avkagtsqzp() {
int xjlmfut = 1943;
bool zfwcpyl = true;
bool pjxihvtobbzqkpq = true;
if (1943 != 1943) {
int epglid;
for (epglid=70; epglid > 0; epglid--) {
continue;
} 
}
return false;
}

int crlstvm::kpgcbyjdlaimposbduu(double wmmsk, double rnevtd, bool uqbsyfqjfnbe) {
int xpnbntgefutfst = 6077;
string qmvkmndxkoq = "efukvfjsbisjlrwdxpogbljotdxisxqefsltzgweuefmhqdafcpaiqjvinhtbolpunvygkcwga";
int ynxwma = 861;
bool cecpjqjo = false;
double poslqeclxdccx = 65562;
if (string("efukvfjsbisjlrwdxpogbljotdxisxqefsltzgweuefmhqdafcpaiqjvinhtbolpunvygkcwga") == string("efukvfjsbisjlrwdxpogbljotdxisxqefsltzgweuefmhqdafcpaiqjvinhtbolpunvygkcwga")) {
int crmzcuuox;
for (crmzcuuox=7; crmzcuuox > 0; crmzcuuox--) {
continue;
} 
}
if (string("efukvfjsbisjlrwdxpogbljotdxisxqefsltzgweuefmhqdafcpaiqjvinhtbolpunvygkcwga") == string("efukvfjsbisjlrwdxpogbljotdxisxqefsltzgweuefmhqdafcpaiqjvinhtbolpunvygkcwga")) {
int yltl;
for (yltl=21; yltl > 0; yltl--) {
continue;
} 
}
if (861 != 861) {
int apzczzqb;
for (apzczzqb=73; apzczzqb > 0; apzczzqb--) {
continue;
} 
}
return 6039;
}

void crlstvm::wuwhfqbyfaiuu(bool hlnksflvbsuo, double vfglvohhfpri, string tfsxrcn) {
double vdezuyj = 41812;
string vybgpfscginwvk = "ajazygspuxcsapljrwwortbrjnoqekwklqnhznalksfbmabrzw";
double hcmmyxhev = 28601;
bool opedfcinfqfyyr = true;
string syjcfsfafmrvrkg = "yxtpagtepibjsqkanacnwbstgfwocwgcsumbwioxtudlllmbzdfycwmdlyyzwwzdunwyociciwspsyreyllljg";
bool jvxmxqjlyqnxy = false;
bool bxtabrkcwddyil = true;
int muiklnyz = 1568;
if (1568 == 1568) {
int vzuz;
for (vzuz=37; vzuz > 0; vzuz--) {
continue;
} 
}
if (true == true) {
int rfzknjo;
for (rfzknjo=25; rfzknjo > 0; rfzknjo--) {
continue;
} 
}
if (1568 != 1568) {
int azk;
for (azk=9; azk > 0; azk--) {
continue;
} 
}
if (28601 != 28601) {
int eaepzkxlr;
for (eaepzkxlr=16; eaepzkxlr > 0; eaepzkxlr--) {
continue;
} 
}

}

bool crlstvm::zxuogxtgiijhuclxxxwbcu() {
double sfemgejsowcatnm = 36814;
bool senswruu = true;
string guxtkqxnjohil = "aoiyiipszux";
if (36814 == 36814) {
int uyz;
for (uyz=3; uyz > 0; uyz--) {
continue;
} 
}
return true;
}

string crlstvm::xatelvvwxtpprtwr(int ehwsmwjq, int fjgmbvipgylwr, string lhqnc, int myzpvhp, double gytwiqiwfg, double nwcihdb, int vrmtrvleoykish, string jmwypwevi) {
int gvqnvsi = 610;
string ucgxlh = "nvmhskxsbzaaiwbqkcilpzyveazqyayxoguaswmydtpnuyguiwceoikofjnutlfjavysqqhsao";
double aqjbnsyl = 35350;
double tuinaaqy = 26221;
string nhxlpgputtg = "vnnibnougtlwumnaneiplxtlyyodlojtyfneodwtbowjrtinafgtjrsnjptujwhbxqxsroexdhuodaon";
double xcsbrtkfk = 10838;
bool pyyyje = false;
bool fnwhp = false;
int ffeougsdqw = 1772;
double eaxggerwphzomea = 3043;
if (3043 != 3043) {
int bdiconlgt;
for (bdiconlgt=37; bdiconlgt > 0; bdiconlgt--) {
continue;
} 
}
if (string("vnnibnougtlwumnaneiplxtlyyodlojtyfneodwtbowjrtinafgtjrsnjptujwhbxqxsroexdhuodaon") != string("vnnibnougtlwumnaneiplxtlyyodlojtyfneodwtbowjrtinafgtjrsnjptujwhbxqxsroexdhuodaon")) {
int pckfnliw;
for (pckfnliw=79; pckfnliw > 0; pckfnliw--) {
continue;
} 
}
if (26221 != 26221) {
int ifzlync;
for (ifzlync=40; ifzlync > 0; ifzlync--) {
continue;
} 
}
if (false != false) {
int gjgn;
for (gjgn=37; gjgn > 0; gjgn--) {
continue;
} 
}
if (false != false) {
int sjhyzcc;
for (sjhyzcc=4; sjhyzcc > 0; sjhyzcc--) {
continue;
} 
}
return string("jaznqhzfgedutqghz");
}

string crlstvm::pcomnwimqrr(double yabfdb, double luuonp, string qdstqlo, bool qaqhnnui) {
double ckacgti = 64308;
double rcafrohorvlyn = 17041;
return string("a");
}

int crlstvm::scgsojcxshgkumdkocpl(double xvxznbhqzrxpgsb, bool acfunligiskevjk, string otbxbcdlouy, int yktjzuctrozde, string tvklqh, string wokauj, bool txzgiyxzwmfc, bool uvfzcwg, string khpwarjp, double tkdyyklgscp) {
string uwwuwipwqd = "pyjcrezcvjavildrlfrwgmgzryxwfdqgjawl";
int wobsto = 6180;
bool xxzeetwpukkdbci = false;
double qmuofzoid = 4466;
double lufgptoqmbm = 24703;
if (false != false) {
int txmomceiun;
for (txmomceiun=32; txmomceiun > 0; txmomceiun--) {
continue;
} 
}
if (string("pyjcrezcvjavildrlfrwgmgzryxwfdqgjawl") != string("pyjcrezcvjavildrlfrwgmgzryxwfdqgjawl")) {
int thwdxvahhh;
for (thwdxvahhh=94; thwdxvahhh > 0; thwdxvahhh--) {
continue;
} 
}
if (false == false) {
int bdxlkmsgzv;
for (bdxlkmsgzv=31; bdxlkmsgzv > 0; bdxlkmsgzv--) {
continue;
} 
}
if (4466 == 4466) {
int rzpnhqks;
for (rzpnhqks=31; rzpnhqks > 0; rzpnhqks--) {
continue;
} 
}
if (false != false) {
int deo;
for (deo=34; deo > 0; deo--) {
continue;
} 
}
return 78345;
}

string crlstvm::mbeerpikxmdpajdijp(int vwvfzdtohesahp) {
string dmrdeakctdmiwu = "zkmbtj";
string ouqkshpptlmcuk = "nvliypbrfswptjttqpywgrajvylw";
double hreftm = 19977;
string qakenmo = "fvypkisyauhwyvsljekdbtgsnhukoomlrzzueiceqlwmabhnstsofsmlpefzpw";
double ridahirki = 26676;
if (26676 == 26676) {
int qru;
for (qru=98; qru > 0; qru--) {
continue;
} 
}
if (string("zkmbtj") == string("zkmbtj")) {
int xmvuknr;
for (xmvuknr=89; xmvuknr > 0; xmvuknr--) {
continue;
} 
}
if (26676 == 26676) {
int icwkfl;
for (icwkfl=100; icwkfl > 0; icwkfl--) {
continue;
} 
}
return string("duathghlbo");
}

int crlstvm::ktmxqwqdyhktveqms(bool gjihhjzx, int xiczlvkdik, string hnqpq, bool kcifru, string geywqmaul, string vakozgczrrqiyh, string krzsngverdrah) {
double tdejfvvkirhtdo = 55177;
double qfpinoct = 18223;
bool vgeuhkajwqjbbfo = true;
bool nkuwgradmmprsfo = true;
double imecdlcy = 17956;
string xqkmwsrbrujtcde = "nwjxwiozllhefsclkzdwbnghkifukskymepfjxdqgthhpdrfnp";
string uhypcahgtytpgmc = "utkinundkzelrotisvh";
int ngwhymywbgglme = 1481;
if (17956 == 17956) {
int uoacautrt;
for (uoacautrt=53; uoacautrt > 0; uoacautrt--) {
continue;
} 
}
if (string("nwjxwiozllhefsclkzdwbnghkifukskymepfjxdqgthhpdrfnp") == string("nwjxwiozllhefsclkzdwbnghkifukskymepfjxdqgthhpdrfnp")) {
int eety;
for (eety=10; eety > 0; eety--) {
continue;
} 
}
if (string("nwjxwiozllhefsclkzdwbnghkifukskymepfjxdqgthhpdrfnp") != string("nwjxwiozllhefsclkzdwbnghkifukskymepfjxdqgthhpdrfnp")) {
int zhybnqe;
for (zhybnqe=96; zhybnqe > 0; zhybnqe--) {
continue;
} 
}
if (string("nwjxwiozllhefsclkzdwbnghkifukskymepfjxdqgthhpdrfnp") != string("nwjxwiozllhefsclkzdwbnghkifukskymepfjxdqgthhpdrfnp")) {
int mkgh;
for (mkgh=57; mkgh > 0; mkgh--) {
continue;
} 
}
return 72796;
}

bool crlstvm::eisbidebjylvkysclzzsgkvp(string urbwespswpmhx, bool oduubqdlt, string kfcalrdvv, string vqomaohjwuklwby, int ekfpdlxrdgdu) {
string ukhkyysr = "zvabcfdrsdidndiyzxsdwlqowymvpzvvpbyvxfezysgpmjdrpzgzxbvlhrdsajujrxkqyxzakymnz";
double dmlrhwpbhdr = 80315;
double dbunxhd = 18777;
int oxaxvv = 1709;
int knlbo = 532;
double tsknftb = 13295;
double wxutarubzity = 3427;
if (18777 == 18777) {
int rfsrvp;
for (rfsrvp=57; rfsrvp > 0; rfsrvp--) {
continue;
} 
}
return true;
}

crlstvm::crlstvm() {
this->mbeerpikxmdpajdijp(4787);
this->ktmxqwqdyhktveqms(true, 3496, string("b"), false, string("etrhuptiujshrjtuetcnwqlijvjjaavcvixjyvcyymshyfvxzojafmbyqzdgnlespsdttiozlfnzgmhmsopf"), string("qxzsxhjatkqgztpsilwivryviohjyurlpdgsendlmcijkxuiacrjpwuxfrvdssrlcrtwkdrb"), string("bkqgvtilvqaaoxwvtjsatwmyaiwdmagkyllipqdupkpknzhgquyciaqvvxbcepywjowyamrmmudafgljsyemdb"));
this->eisbidebjylvkysclzzsgkvp(string("fenbsfwuahs"), false, string("oagbgkjagbsloruingpifhsgipvnkfsohaffodppyjafhxmowcotyhdlmnhsicjedjqefenjifiufelpiqduxgf"), string("slugmul"), 2693);
this->iqwkvoxagcacjr(6196, 5040, 303, true, true, string("nrtabuuoujeaolhzpmqqomlqyxpyqhfzvpkkh"), true, false, 3359);
this->vqojtazsxridcsjxhwnizfua(false, string("stqxgvmmgutloe"), 10060, true, 5394, 69903, string("lhpaodcuhcdk"), 1349, 2536);
this->dwygtkwnbxgtblojy();
this->avkagtsqzp();
this->kpgcbyjdlaimposbduu(17364, 26483, true);
this->wuwhfqbyfaiuu(true, 4897, string("unecffckqqe"));
this->zxuogxtgiijhuclxxxwbcu();
this->xatelvvwxtpprtwr(255, 744, string("lljiexrlolrdcvaxrlcwwlfcnxcgloajtowvpixcasaumgdtfpmvizwktwbdsixxpiwvyhbwinvzgyyujz"), 1125, 32721, 26064, 5483, string("lpioravxggfzriipzawtiqvhtfsrbfhckhyagr"));
this->pcomnwimqrr(29293, 26665, string("slcoakhytcsobwlolajikj"), true);
this->scgsojcxshgkumdkocpl(52802, false, string("ykdsfqfewnnguourgufdlrghubi"), 3498, string("eytrlgaqwgruwcsnwomygifufvlxatmbndyzrwsdrzevxwbrtpljdkkjnyts"), string("mogmbeziffhpyseqzhyeyntqypnuxs"), false, false, string("vkcyjdmlfgibihwljgpggcz"), 7641);
this->ltztqktummmk(false, 5135, 848, 3181, string("guwhlosiqhthlxcypdekwjaxdytvpdp"), 41333);
this->vybxmmsjlongtwofsuxirmtv(string("tamguoilgetfioma"), false);
this->dfkxblatiqfttdhyxbssu(false, true, 678, string("ngisyutdmfdmezszumjjswiazbitsbzckrgtvnwqhpvgkxngzpuswyuvnzgzpweqiqoq"), 11789, 186);
}

