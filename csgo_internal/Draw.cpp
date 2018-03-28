#include "Cheat.h"

HFont F::Meme;
HFont F::ESP;
HFont F::Watermark;

void D::SetupFonts()
{
	// fuck these non windows fonts
	I::Surface->SetFontGlyphSet( F::Meme = I::Surface->Create_Font(), charenc( "Comic Sans MS" ), 30, FW_DONTCARE, NULL, NULL, FONTFLAG_ANTIALIAS );
	I::Surface->SetFontGlyphSet( F::ESP = I::Surface->Create_Font(), charenc( "Consolas" ), 12, FW_DONTCARE, NULL, NULL, FONTFLAG_OUTLINE );
	I::Surface->SetFontGlyphSet( F::Watermark = I::Surface->Create_Font(), charenc( "MS Sans Serif" ), 12, FW_DONTCARE, NULL, NULL, FONTFLAG_OUTLINE );
}

void D::DrawString( HFont font, int x, int y, Color color, DWORD alignment, const char* msg, ... )
{
	va_list va_alist;
	char buf[1024];
	va_start( va_alist, msg );
	_vsnprintf( buf, sizeof( buf ), msg, va_alist );
	va_end( va_alist );
	wchar_t wbuf[1024];
	MultiByteToWideChar( CP_UTF8, 0, buf, 256, wbuf, 256 );

	int r = 255, g = 255, b = 255, a = 255;
	color.GetColor( r, g, b, a );

	int width, height;
	I::Surface->GetTextSize( font, wbuf, width, height );

	if( alignment & FONT_RIGHT )
		x -= width;
	if( alignment & FONT_CENTER )
		x -= width / 2;

	I::Surface->DrawSetTextFont( font );
	I::Surface->DrawSetTextColor( r, g, b, a );
	I::Surface->DrawSetTextPos( x, y - height / 2 );
	I::Surface->DrawPrintText( wbuf, wcslen( wbuf ) );
}

void D::DrawStringUnicode( HFont font, int x, int y, Color color, bool bCenter, const wchar_t* msg, ... )
{
	int r = 255, g = 255, b = 255, a = 255;
	color.GetColor( r, g, b, a );

	int iWidth, iHeight;

	I::Surface->GetTextSize( font, msg, iWidth, iHeight );
	I::Surface->DrawSetTextFont( font );
	I::Surface->DrawSetTextColor( r, g, b, a );
	I::Surface->DrawSetTextPos( !bCenter ? x : x - iWidth / 2, y - iHeight / 2 );
	I::Surface->DrawPrintText( msg, wcslen( msg ) );
}

void D::DrawRect( int x, int y, int w, int h, Color col )
{
	I::Surface->DrawSetColor( col );
	I::Surface->DrawFilledRect( x, y, x + w, y + h );
}

void D::DrawRectRainbow( int x, int y, int width, int height, float flSpeed, float& flRainbow )
{
	Color colColor( 0, 0, 0 );

	flRainbow += flSpeed;
	if( flRainbow > 1.f )
		flRainbow = 0.f;

	for( int i = 0; i < width; i++ )
	{
		float hue = ( 1.f / ( float ) width ) * i;
		hue -= flRainbow;
		if( hue < 0.f )
			hue += 1.f;

		Color colRainbow = colColor.FromHSB( hue, 1.f, 1.f );
		D::DrawRect( x + i, y, 1, height, colRainbow );
	}
}

void D::DrawRectGradientHorizontal( int x, int y, int width, int height, Color color1, Color color2 )
{
	float flDifferenceR = ( float ) ( color2.r() - color1.r() ) / ( float ) width;
	float flDifferenceG = ( float ) ( color2.g() - color1.g() ) / ( float ) width;
	float flDifferenceB = ( float ) ( color2.b() - color1.b() ) / ( float ) width;

	for( float i = 0.f; i < width; i++ )
	{
		Color colGradient = Color( color1.r() + ( flDifferenceR * i ), color1.g() + ( flDifferenceG * i ), color1.b() + ( flDifferenceB * i ), color1.a() );
		D::DrawRect( x + i, y, 1, height, colGradient );
	}
}

void D::DrawPixel( int x, int y, Color col )
{
	I::Surface->DrawSetColor( col );
	I::Surface->DrawFilledRect( x, y, x + 1, y + 1 );
}

void D::DrawOutlinedRect( int x, int y, int w, int h, Color col )
{
	I::Surface->DrawSetColor( col );
	I::Surface->DrawOutlinedRect( x, y, x + w, y + h );
}

void D::DrawOutlinedCircle( int x, int y, int r, Color col )
{
	I::Surface->DrawSetColor( col );
	I::Surface->DrawOutlinedCircle( x, y, r, 1 );
}

void D::DrawLine( int x0, int y0, int x1, int y1, Color col )
{
	I::Surface->DrawSetColor( col );
	I::Surface->DrawLine( x0, y0, x1, y1 );
}

void D::DrawCorner( int iX, int iY, int iWidth, int iHeight, bool bRight, bool bDown, Color colDraw )
{
	int iRealX = bRight ? iX - iWidth : iX;
	int iRealY = bDown ? iY - iHeight : iY;

	if( bDown && bRight )
		iWidth = iWidth + 1;

	D::DrawRect( iRealX, iY, iWidth, 1, colDraw );
	D::DrawRect( iX, iRealY, 1, iHeight, colDraw );

	D::DrawRect( iRealX, bDown ? iY + 1 : iY - 1, !bDown && bRight ? iWidth + 1 : iWidth, 1, Color( 0, 0, 0, 255 ) );
	D::DrawRect( bRight ? iX + 1 : iX - 1, bDown ? iRealY : iRealY - 1, 1, bDown ? iHeight + 2 : iHeight + 1, Color( 0, 0, 0, 255 ) );
}

void D::DrawPolygon( int count, Vertex_t* Vertexs, Color color )
{
	static int Texture = I::Surface->CreateNewTextureID( true );
	unsigned char buffer[4] = { 255, 255, 255, 255 };

	I::Surface->DrawSetTextureRGBA( Texture, buffer, 1, 1 );
	I::Surface->DrawSetColor( color );
	I::Surface->DrawSetTexture( Texture );

	I::Surface->DrawTexturedPolygon( count, Vertexs );
}

void D::DrawRoundedBox( int x, int y, int w, int h, int r, int v, Color col )
{
	std::vector< Vertex_t > p;
	for( int _i = 0; _i < 3; _i++ )
	{
		int _x = x + ( _i < 2 && r || w - r );
		int _y = y + ( _i % 3 > 0 && r || h - r );
		for( int i = 0; i < v; i++ )
		{
			int a = RAD2DEG( ( i / v ) * -90 - _i * 90 );
			p.push_back( Vertex_t( Vector2D( _x + sin( a ) * r, _y + cos( a ) * r ) ) );
		}
	}

	D::DrawPolygon( 4 * ( v + 1 ), &p[ 0 ], col );
	/*
	function DrawRoundedBox(x, y, w, h, r, v, col)
	local p = {};
	for _i = 0, 3 do
	local _x = x + (_i < 2 && r || w - r)
	local _y = y + (_i%3 > 0 && r || h - r)
	for i = 0, v do
	local a = math.rad((i / v) * - 90 - _i * 90)
	table.insert(p, {x = _x + math.sin(a) * r, y = _y + math.cos(a) * r})
	end
	end

	surface.SetDrawColor(col.r, col.g, col.b, 255)
	draw.NoTexture()
	surface.DrawPoly(p)
	end
	*/

	// Notes: amount of vertexes is 4(v + 1) where v is the number of vertices on each corner bit.
	// I did it in lua cause I have no idea how the vertex_t struct works and i'm still aids at C++
}

bool D::ScreenTransform( const Vector& point, Vector& screen ) // tots not pasted
{
	float w;
	const VMatrix& worldToScreen = I::Engine->WorldToScreenMatrix();

	screen.x = worldToScreen[ 0 ][ 0 ] * point[ 0 ] + worldToScreen[ 0 ][ 1 ] * point[ 1 ] + worldToScreen[ 0 ][ 2 ] * point[ 2 ] + worldToScreen[ 0 ][ 3 ];
	screen.y = worldToScreen[ 1 ][ 0 ] * point[ 0 ] + worldToScreen[ 1 ][ 1 ] * point[ 1 ] + worldToScreen[ 1 ][ 2 ] * point[ 2 ] + worldToScreen[ 1 ][ 3 ];
	w = worldToScreen[ 3 ][ 0 ] * point[ 0 ] + worldToScreen[ 3 ][ 1 ] * point[ 1 ] + worldToScreen[ 3 ][ 2 ] * point[ 2 ] + worldToScreen[ 3 ][ 3 ];
	screen.z = 0.0f;

	bool behind = false;

	if( w < 0.001f )
	{
		behind = true;
		screen.x *= 100000;
		screen.y *= 100000;
	}
	else
	{
		behind = false;
		float invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
	}

	return behind;
}

bool D::WorldToScreen( const Vector& origin, Vector& screen )
{
	if( !ScreenTransform( origin, screen ) )
	{
		int ScreenWidth, ScreenHeight;
		I::Engine->GetScreenSize( ScreenWidth, ScreenHeight );
		float x = ScreenWidth / 2;
		float y = ScreenHeight / 2;
		x += 0.5 * screen.x * ScreenWidth + 0.5;
		y -= 0.5 * screen.y * ScreenHeight + 0.5;
		screen.x = x;
		screen.y = y;
		return true;
	}

	return false;
}

int D::GetStringWidth( HFont font, const char* msg, ... )
{
	va_list va_alist;
	char buf[1024];
	va_start( va_alist, msg );
	_vsnprintf( buf, sizeof( buf ), msg, va_alist );
	va_end( va_alist );
	wchar_t wbuf[1024];
	MultiByteToWideChar( CP_UTF8, 0, buf, 256, wbuf, 256 );

	int iWidth, iHeight;

	I::Surface->GetTextSize( font, wbuf, iWidth, iHeight );

	return iWidth;
}

void D::Draw3DBox( Vector* boxVectors, Color color )
{
	Vector boxVectors0, boxVectors1, boxVectors2, boxVectors3,
	       boxVectors4, boxVectors5, boxVectors6, boxVectors7;

	if( D::WorldToScreen( boxVectors[ 0 ], boxVectors0 ) &&
		D::WorldToScreen( boxVectors[ 1 ], boxVectors1 ) &&
		D::WorldToScreen( boxVectors[ 2 ], boxVectors2 ) &&
		D::WorldToScreen( boxVectors[ 3 ], boxVectors3 ) &&
		D::WorldToScreen( boxVectors[ 4 ], boxVectors4 ) &&
		D::WorldToScreen( boxVectors[ 5 ], boxVectors5 ) &&
		D::WorldToScreen( boxVectors[ 6 ], boxVectors6 ) &&
		D::WorldToScreen( boxVectors[ 7 ], boxVectors7 ) )
	{
		/*
			   .+--5---+
			 .8 4    6'|
			+--7---+'  11
			9   |  10  |
			|  ,+--|3--+
			|.0    | 2'
			+--1---+'
		*/

		Vector2D lines[ 12 ][ 2 ];
		//bottom of box
		lines[ 0 ][ 0 ] = { boxVectors0.x, boxVectors0.y };
		lines[ 0 ][ 1 ] = { boxVectors1.x, boxVectors1.y };
		lines[ 1 ][ 0 ] = { boxVectors1.x, boxVectors1.y };
		lines[ 1 ][ 1 ] = { boxVectors2.x, boxVectors2.y };
		lines[ 2 ][ 0 ] = { boxVectors2.x, boxVectors2.y };
		lines[ 2 ][ 1 ] = { boxVectors3.x, boxVectors3.y };
		lines[ 3 ][ 0 ] = { boxVectors3.x, boxVectors3.y };
		lines[ 3 ][ 1 ] = { boxVectors0.x, boxVectors0.y };

		lines[ 4 ][ 0 ] = { boxVectors0.x, boxVectors0.y };
		lines[ 4 ][ 1 ] = { boxVectors6.x, boxVectors6.y };

		// top of box
		lines[ 5 ][ 0 ] = { boxVectors6.x, boxVectors6.y };
		lines[ 5 ][ 1 ] = { boxVectors5.x, boxVectors5.y };
		lines[ 6 ][ 0 ] = { boxVectors5.x, boxVectors5.y };
		lines[ 6 ][ 1 ] = { boxVectors4.x, boxVectors4.y };
		lines[ 7 ][ 0 ] = { boxVectors4.x, boxVectors4.y };
		lines[ 7 ][ 1 ] = { boxVectors7.x, boxVectors7.y };
		lines[ 8 ][ 0 ] = { boxVectors7.x, boxVectors7.y };
		lines[ 8 ][ 1 ] = { boxVectors6.x, boxVectors6.y };

		lines[ 9 ][ 0 ] = { boxVectors5.x, boxVectors5.y };
		lines[ 9 ][ 1 ] = { boxVectors1.x, boxVectors1.y };

		lines[ 10 ][ 0 ] = { boxVectors4.x, boxVectors4.y };
		lines[ 10 ][ 1 ] = { boxVectors2.x, boxVectors2.y };

		lines[ 11 ][ 0 ] = { boxVectors7.x, boxVectors7.y };
		lines[ 11 ][ 1 ] = { boxVectors3.x, boxVectors3.y };

		for( int i = 0; i < 12; i++ )
		{
			D::DrawLine( lines[ i ][ 0 ].x, lines[ i ][ 0 ].y, lines[ i ][ 1 ].x, lines[ i ][ 1 ].y, color );
		}
	}
}

void D::DrawCircle( float x, float y, float r, float s, Color color )
{
	float Step = M_PI * 2.0 / s;
	for( float a = 0; a < ( M_PI * 2.0 ); a += Step )
	{
		float x1 = r * cos( a ) + x;
		float y1 = r * sin( a ) + y;
		float x2 = r * cos( a + Step ) + x;
		float y2 = r * sin( a + Step ) + y;

		DrawLine( x1, y1, x2, y2, color );
	}
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


