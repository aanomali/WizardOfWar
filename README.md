# Wizard of Wor (C++ Oyun Projesi)

## Proje Özeti
**Wizard of Wor**, klasik arcade labirent-shooter oyunlarından esinlenilerek geliştirilmiş, C++ tabanlı 2D bir oyun projesidir. 
Proje; modern oyun motorları (Unity, Unreal vb.) kullanılmadan, **düşük seviyede grafik çizimi**, **klavye tabanlı girdi işleme**, 
**oyun döngüsü (game loop)** ve **durum yönetimi (state management)** gibi temel oyun programlama kavramlarını uygulamayı amaçlar.

Bu çalışma, **akademik ders projeleri**, **GitHub portföyü** ve **CV/LinkedIn** kullanımı için uygun şekilde tasarlanmıştır.

---

## Kullanılan Teknolojiler
- **Programlama Dili:** C++
- **Grafik & Varlıklar (Assets):** Bitmap (.bmp) tabanlı 2D sprite’lar
- **Geliştirme Ortamı:** Microsoft Visual Studio (Windows)
- **Programlama Yaklaşımı:** Prosedürel yapı + olay tabanlı oyun döngüsü

---

## Proje Yapısı
Proje yapısı, kontrol akışının ve temel mantığın net şekilde takip edilebilmesi için sade tutulmuştur:

```text
WizardOfWor/
├── Main.cpp                     # Uygulama giriş noktası ve ana oyun döngüsü
├── Wizard of Wor.sln            # Visual Studio çözüm dosyası
├── Wizard of Wor.vcxproj        # Proje yapılandırması
├── Wizard of Wor.vcxproj.filters
├── Wizard of Wor.vcxproj.user
├── map.bmp                     # Oyun haritası
├── Enemyleft11.bmp              # Düşman sprite’ı
├── deadanim2.bmp                # Ölüm animasyonu
├── gameover.bmp                 # Oyun sonu ekranı
├── congr.bmp                    # Kazanma ekranı
└── README.md
```

---

## Oynanış ve Teknik Özellikler
- **Oyun Döngüsü (Game Loop)**
  - Sürekli çalışan update–render döngüsü
  - Akış: *Input → Update → Render*
- **Girdi (Input) Yönetimi**
  - Klavye ile oyuncu kontrolü
  - Gerçek zamanlı olay işleme
- **Rendering Sistemi**
  - Bitmap tabanlı sprite çizimi
  - Statik ve animasyonlu görseller
- **Oyun Mantığı**
  - Oyuncu–düşman etkileşimi
  - Çarpışmaya dayalı sonuçlar (ölüm / kazanma)
- **Durum (State) Yönetimi**
  - Oynanış, oyun sonu ve başarı durumları

Bu yapı, klasik arcade oyunlarının temel teknik prensiplerini yansıtır.

---

## Kurulum ve Çalıştırma

### Gereksinimler
- Windows
- **Visual Studio** (Desktop Development with C++ bileşeni yüklü)

### Adımlar
1. Bu repository’yi klonlayın:
   ```bash
   git clone <repository-url>
   ```

2. `Wizard of Wor.sln` dosyasını Visual Studio ile açın.

3. Varsayılan yapılandırma ile projeyi derleyin.

4. Uygulamayı Visual Studio üzerinden çalıştırın.

> Not: `.bmp` uzantılı varlık dosyalarının (asset) çalıştırılabilir dosya ile aynı dizinde veya doğru göreli yolda bulunması gerekmektedir.

---

## Akademik / CV Odaklı Kazanımlar
Bu proje kapsamında:
- C++ ile **tam bir 2D oyun döngüsü** geliştirme,
- Düşük seviyede grafik ve girdi yönetimi,
- Bitmap tabanlı varlık (asset) kullanımı,
- Temel çarpışma ve durum mantığı tasarımı,
- Klasik arcade oyun mekaniklerinin anlaşılması  
konularında pratik deneyim kazanılmıştır.

---

## Geliştirme Fikirleri (Gelecek Çalışmalar)
- Nesne yönelimli mimariye geçiş (Player / Enemy / Engine ayrımı)
- Daha hassas çarpışma algılama
- Ses ve müzik entegrasyonu
- Çoklu seviye ve artan zorluk
- Skor ve liderlik tablosu sistemi

---

## Lisans
Bu proje eğitim amaçlı geliştirilmiştir.  
Görsel varlıklar ticari olmayan, akademik kullanım içindir.
