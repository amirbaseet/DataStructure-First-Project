/**
 * @file main.cpp
 * @description Programınızın açıklaması ne yaptığına dair.
 * @course 2C
 * @assignment birinci ödev
 * @date 1/12/2022
 * @author AMRO MOUSA ISMAIL BASEET
 */
#include <Dugum.hpp>
#include <SatirListesi.hpp>
#include <YoneticiDugum.hpp>
#include <YoneticiListesi.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;
void solaGit(float &sayfa_Adet, float &burayakadar_yazdir, float &Baslangic) // sol sayfa varsa giden bir fonksiyon
{

     if (sayfa_Adet - burayakadar_yazdir != sayfa_Adet - 1) // Eger ilk sayfada bulunmuyorsa onceki sayfa Yazdir
     {
          if (sayfa_Adet - burayakadar_yazdir > 0) // Eger son sayfada degil ve birinci sayfada da degil ise burda gersin
          {
               burayakadar_yazdir--;
          }
          else if (sayfa_Adet - burayakadar_yazdir == 0)
          {

               // eger tum elemanlari yazdirildi ise .000 kurtalmak icin
               burayakadar_yazdir = Baslangic / 8;
          }

          if (burayakadar_yazdir >= 1)
          { // Eger burayakadar_yazdir 8 taneden buyuk ise baslangic =burayakadar_yazdir -8
               Baslangic = burayakadar_yazdir - 1;
          }
          else
          {
               Baslangic = 0;
          }
          Baslangic *= 8;
     }
}
void SagGit(float &sayfa_Adet, float &burayakadar_yazdir, const int &YD_Dugumsayisi, float &Baslangic)
{ // sag sayfa varsa giden bir fonksiyon
     if (burayakadar_yazdir * 8 != YD_Dugumsayisi)
     {
          Baslangic = burayakadar_yazdir * 8;

          if (sayfa_Adet - burayakadar_yazdir >= 1)
          {
               burayakadar_yazdir++;
          }
          else if (sayfa_Adet - burayakadar_yazdir > 0 && sayfa_Adet - burayakadar_yazdir < 1)
          {

               burayakadar_yazdir += (sayfa_Adet - burayakadar_yazdir);
          }
     }
}
void YD_sil_sonra(float &Baslangic, float &burayakadar_yazdir, float &sayfa_Adet)
{
     if (Baslangic == ((burayakadar_yazdir * 8) - 1)) // Eger Sayfada Tek Dugum Varsa silindikten sonra Sayfada Hic Bir dugum kalmadiginden  onceki Sayfa ya Yazdirilacak
     {
          solaGit(sayfa_Adet, burayakadar_yazdir, Baslangic);
     }
     else if (burayakadar_yazdir == sayfa_Adet)
     {
          burayakadar_yazdir *= 8;
          burayakadar_yazdir--;
          burayakadar_yazdir /= 8;
     }
}

Y_Dugum *sonraki_sayfa_birinciD_sec(const float &Baslangic, Y_Dugum *secilen_YDugum, int &secilen)
{ // sag yada sol sayfa giderken yeni sayfada ilk Ydugum secen bir fonksiyon
     for (int i = 0; i < Baslangic; i++)
     {
          /* code */
          secilen_YDugum = secilen_YDugum->sonraki; // bu yeni Sayfanin ilk dugumu olacak
     }
     secilen = 0;
     return secilen_YDugum;
}
Y_Dugum *Onceki_sayfa_SonD_sec(const float &Baslangic, const float &bitis, Y_Dugum *secilen_YDugum, int &secilen)
{                                              // sag yada sol sayfa giderken yeni sayfada ilk Ydugum secen bir fonksiyon
     for (int i = 0; i < (bitis * 8) - 1; i++) // bitis*8 -1 cunku bitis son yazdirilanin sonraki issetir 8
     {
          /* code */
          secilen_YDugum = secilen_YDugum->sonraki; // bu yeni Sayfanin ilk dugumu olacak
     }
     secilen = (bitis * 8 - 1) - Baslangic;
     return secilen_YDugum;
}
Y_Dugum *Siralama_sonra_YDsec(Y_Dugum *secilen_YDugum, Y_Dugum *ilk, const int &secilen, const float &Baslangic)
{
     int dugum_indeksi = secilen + Baslangic;
     secilen_YDugum = ilk;
     for (int i = 0; i < dugum_indeksi; i++)
     {
          /* code */
          secilen_YDugum = secilen_YDugum->sonraki; // bu yeni Sayfanin ilk dugumu olacak
     }
     return secilen_YDugum;
}
Y_Dugum *sonraki_Dugum_git(Y_Dugum *secilen_YDugum, float &sayfa_Ade, const int &YD_Dugumsayisi, Y_Dugum *ilk, int &secilen, float &burayakadar_yazdir, float &Baslangic)
{
     if (secilen_YDugum->sonraki != 0 && secilen < (burayakadar_yazdir * 8 - Baslangic - 1))
     {
          /* Eger Secilen Dugum son ve sayfada son dugum ise sonrasina gitmez*/
          cout << "\n104\n";
          secilen++;
          secilen_YDugum = secilen_YDugum->sonraki;
     }
     else if (secilen_YDugum->sonraki != 0 && secilen == (burayakadar_yazdir * 8 - Baslangic - 1))
     {
          cout << "\n110\n";
          SagGit(sayfa_Ade, burayakadar_yazdir, YD_Dugumsayisi, Baslangic);
          secilen_YDugum = ilk;
          secilen_YDugum = sonraki_sayfa_birinciD_sec(Baslangic, secilen_YDugum, secilen);
     }

     return secilen_YDugum;
}
Y_Dugum *Onceki_Dugum_git(Y_Dugum *secilen_YDugum, float &sayfa_Ade, const int &YD_Dugumsayisi, Y_Dugum *ilk, int &secilen, float &burayakadar_yazdir, float &Baslangic)
{
     if (secilen_YDugum != ilk)
     {
          if (secilen != 0)
          {
               /*Eger Secilen Dugumun Onceki Dugumun adresi 0 degil ise onceki gitmez */
               secilen--;
               secilen_YDugum = secilen_YDugum->onceki;
          }
          else if (secilen == 0 && secilen_YDugum->onceki != 0)
          {

               solaGit(sayfa_Ade, burayakadar_yazdir, Baslangic);
               secilen_YDugum = ilk;
               secilen_YDugum = Onceki_sayfa_SonD_sec(Baslangic, burayakadar_yazdir, secilen_YDugum, secilen);
          }
     }
     return secilen_YDugum;
}
int main()
{

     //////////////////////////////////FILE DEN OKUMA ISLEMLERI BASLANGICI///////////////////////////////////////////////////////////////
     ifstream myfile("src/veriler.txt");
     // read line
     int sayac = 0;
     string satir;
     string bosluk = " ";
     /* code */
     if (!myfile)
          cout << "HATA\n";
     // ilk once satirlarin sayisini getiriyorum
     while (getline(myfile, satir))
     {
          sayac++;
     }
     cout << sayac << endl;
     myfile.close();
     // satirlistesinden heap te bir dizi olusturuyorum satirlarin sayisi kadar bir  uzuzunlugu sahip
     SatirListesi *okun_st = new SatirListesi[sayac];
     YoneticiListesi *YTest = new YoneticiListesi; // heap te Yonetici listesi olusturuyorum
     myfile.open("src/veriler.txt");
     int Kacinci_sati = 0;

     string str;
     /*
     burda .txt ten satirlari okuyorum
     her satir komple alip sonra o satir da islemler yapiyorum
     ilk olarak satir bosluk kadar okumak sonra bulunan sayi heapte bulunan "okun_st" a ekliyorum
     sonra boluga  kadar siliyorum ve satira son bosluga kadar  ayni islemler yapmak
     bitince sonraki satira gecip ayni islemler yapma
     boyle satirlari bitene kadar
     */
     while (std::getline(myfile, bosluk))
     {
          istringstream ss(bosluk);
          while (getline(ss, str, ' '))
          {
               okun_st[Kacinci_sati].Dugum_Ekle(stoi(str));
          }
          if (okun_st[Kacinci_sati].Dugum_Sayisi_Getir() != 0)
          {
               YTest->Y_Dugum_Ekle(&okun_st[Kacinci_sati]);
          }
          Kacinci_sati++;
     }
     myfile.close();
     //////////////////////////////////FILE DEN OKUMA ISLEMLERI BITISI///////////////////////////////////////////////////////////////

     // ekleme yaptiktan sonra yonetici dugum listesi ortalamasine gore siraliyorum
     YTest->Y_Dugum_Siralama();

     float birblok = 21.2;                               // her bir iki dugumun arasinda uzaklasacak mesafe
     float sayfa_Adet = 0.000;                           // DUGUM SAYISI 8 E BOLUB KAC SAYFA OLDUGUNU BILEBILERIZ
     float burayakadar_yazdir;                           // HANGI DUGUME KADAR YAZDIRILICAK
     float Baslangic = 0.00;                             // HANGI DUGUMDEN YAZDIRMA BASLAMA
     float YD_Dugumsayisi = YTest->YDugumSayisi_Getir(); // YONETICI LISTESINDE DUGUM SAYISI TUTUAN

     int secilen = 0;                            // YAZDIRILICAGINDAN KACINICI DUGUM SIRASI DONDUREN
     int silinecekDugumun_indeksi;               // RASTGELE SILINECEK DUGUMUN INDEKSI TUTAN
     int uzaklasacak_mesafe = birblok * secilen; // UZAKLASACAK MESAFE SECILEN DUGUM KACINCI OLDUGUNU *BIR BLOCK

     char sil_mi; //(SATIR LISTESINDE DUGUM SILME YAPARKEN _)K BASMA KONTROLI=U
     char in;

     Y_Dugum *secilen_YDugum = YTest->ilkGetir();
     Y_Dugum *Silinecek_YD;
     Y_Dugum *ilk;
     Dugum *silinecek_Dugum;

     sayfa_Adet = YD_Dugumsayisi / 8; // DUGUM SAYISI 8 E BOLUB KAC SAYFA OLDUGUNU BILEBILERIZ
     if (YD_Dugumsayisi / 8 >= 1)
     {
          burayakadar_yazdir = 1;
     }
     else
          burayakadar_yazdir = YD_Dugumsayisi / 8;

     // secilen_YDugum = YTest->YL_Sag_Yazdir((burayakadar_yazdirilan - 1) * 8, (burayakadar_yazdirilan)*8, secilen_YDugum);
     char intest;
     do
     {

          if (YTest->ilkGetir())
          {

               YD_Dugumsayisi = YTest->YDugumSayisi_Getir();
               sayfa_Adet = YD_Dugumsayisi / 8; // YONETICI DUGUMLARIN SAYISI HER SEFERDE DEGISEBILDIGI ICIN HER YAZDIRMA ISLEMDEN ONCE SAYFA ADETI HEAPLIYORUM
               uzaklasacak_mesafe = birblok * secilen;

               // system("cls");
               YTest->YL_Sag_Yazdir(Baslangic, burayakadar_yazdir * 8);
               secilen_YDugum->S_Liste->YD_Sat_Dugm_Yazdir(uzaklasacak_mesafe);
               cout << "\nsecilen Dugum  = " << secilen_YDugum << " secilen = " << secilen << "Baslangic = " << Baslangic << "bitis =" << burayakadar_yazdir * 8 << endl;

               cin >> in;
          }
          else
          {
               YTest->YL_Yazdir();
               cout << "HIC BIR DUGUM KALMADIGINDAN BIR SEY GOSTERILMEYECEK  HEAP TE KALAN NESNELER SILIP VE PROGRAM SOLANDIRMAK  ICIN LUTFEN 8 BASIN E\n";
               cin >> intest;
               if (intest == '8')
               {
                    in = '8';
               }
               else
               {
               }
          }

          switch (in)
          {
          case 'd': // 8tane sag git
               SagGit(sayfa_Adet, burayakadar_yazdir, YD_Dugumsayisi, Baslangic);
               ///
               secilen_YDugum = YTest->ilkGetir();
               secilen_YDugum = sonraki_sayfa_birinciD_sec(Baslangic, secilen_YDugum, secilen);

               break;
          case 'a': // 8tane sola git
               solaGit(sayfa_Adet, burayakadar_yazdir, Baslangic);
               secilen_YDugum = YTest->ilkGetir();

               secilen_YDugum = sonraki_sayfa_birinciD_sec(Baslangic, secilen_YDugum, secilen);

               break;

               /*sonraki/onceki YDugum sec case z & c*/
          case 'z': /*Kullanıcı ‘z’ tuşuna bastığında seçili düğüm bir öncekine*/
               secilen_YDugum = Onceki_Dugum_git(secilen_YDugum, sayfa_Adet, YD_Dugumsayisi, YTest->ilkGetir(), secilen, burayakadar_yazdir, Baslangic);

               break;
          case 'c': /*‘c’ tuşuna bastığında bir sonraki düğüme secer*/
               secilen_YDugum = sonraki_Dugum_git(secilen_YDugum, sayfa_Adet, YD_Dugumsayisi, YTest->ilkGetir(), secilen, burayakadar_yazdir, Baslangic);
               break;
          case 'k':
               // secilen ydugmun rastgele secme
               if (YTest->ilkGetir())
               {
                    system("cls");

                    silinecekDugumun_indeksi = secilen_YDugum->S_Liste->Dugum_Sil_rastgele();
                    YTest->YL_Sag_Yazdir(Baslangic, burayakadar_yazdir * 8);
                    silinecek_Dugum = secilen_YDugum->S_Liste->get_D_byindeks(silinecekDugumun_indeksi);
                    secilen_YDugum->S_Liste->YD_silinecek_Sat_Dugm_Yazdir_(silinecek_Dugum, uzaklasacak_mesafe);
                    cin >> sil_mi;
                    if (sil_mi == 'k')
                    {

                         secilen_YDugum->S_Liste->Dugum_Sil(silinecek_Dugum);

                         if (secilen_YDugum->S_Liste->Dugum_Sayisi_Getir() != 0)
                         {
                              secilen_YDugum->Ort_Getir();
                              YTest->Y_Dugum_Siralama();
                              secilen_YDugum = Siralama_sonra_YDsec(secilen_YDugum, YTest->ilkGetir(), secilen, Baslangic);
                         }
                         else
                         {
                              ilk = YTest->ilkGetir(); // ilk dugumu Degiri getirdim
                              if (ilk != 0)            // Eger Hic bir dugum kalmamis ise burada girmez
                              {
                                   Silinecek_YD = secilen_YDugum;

                                   if (secilen != 0) // Eger silinecek Dugum ilk Dugume isset ise secilenden azaltmaz
                                   {

                                        /* code */
                                        secilen--;
                                   }
                                   if (secilen != 0 && secilen == (burayakadar_yazdir * 8 - Baslangic) - 1)
                                   {
                                        secilen--;
                                   }

                                   YTest->Y_Dugumun_Silme(Silinecek_YD); // onu silindikten sonra Y_Dugumun_Silme() fonksiyonda bir kosul koymustum eger hic bir dugum kalmadi ise Yonerici Listesi sil
                                   YD_Dugumsayisi = YTest->YDugumSayisi_Getir();
                                   YD_sil_sonra(Baslangic, burayakadar_yazdir, sayfa_Adet);
                                   secilen_YDugum = Siralama_sonra_YDsec(secilen_YDugum, YTest->ilkGetir(), secilen, Baslangic);
                              }
                         }
                    }
               }
               break;

          case 'p':
               /*p bastiginda Yonetici Dugumu Cikaritilacaktir*/
               ilk = YTest->ilkGetir(); // ilk dugumu Degiri getirdim
               if (ilk != 0)            // Eger Hic bir dugum kalmamis ise burada girmez
               {
                    Silinecek_YD = secilen_YDugum;
                    if (secilen != 0) // Eger silinecek Dugum ilk Dugume isset ise secilenden azaltmaz
                    {

                         /* code */
                         secilen--;
                    }

                    YTest->Y_Dugumun_Silme(Silinecek_YD);
                    YD_Dugumsayisi = YTest->YDugumSayisi_Getir();
                    YD_sil_sonra(Baslangic, burayakadar_yazdir, sayfa_Adet);
                    secilen_YDugum = Siralama_sonra_YDsec(secilen_YDugum, YTest->ilkGetir(), secilen, Baslangic);
               }
               break;

          case '8':
               // program kapatmadan once Heapteki bulunan tum nesneleri silme
               // ikiside sildim cunku tum okunan satirlistesi YTest Listesi olmayacagindan (bos satir olursa Ylistesi eklenmeyecek )o yuzdan heapte kalacak onu silmek delet komutu kullandim
               delete YTest; // Tüm düğümleri sil
               delete[] okun_st;
               break;
          default:
               break;
          }
     } while (in != '8');
}
