# Syslog Yönetim Sistemi

Bu proje, sistem günlük (syslog) kayıtlarını yönetmek için geliştirilmiş bir C uygulamasıdır. Çift yönlü bağlı liste yapısı kullanarak syslog kayıtlarını depolar ve yönetir.

## Özellikler

- Syslog kayıtlarını çift yönlü bağlı listede saklama
- Yeni log kayıtları ekleme
- Öncelik seviyesine göre filtreleme
- Tüm kayıtları görüntüleme
- Otomatik bellek yönetimi

## Sistem Gereksinimleri

- C derleyicisi (GCC önerilir)
- Standard C kütüphaneleri
- En az 64MB RAM
- POSIX uyumlu işletim sistemi

## Derleme

Projeyi derlemek için aşağıdaki komutu kullanın:

```bash
gcc -o syslog_manager main.c
```

## Kullanım

Program çalıştırıldığında, örnek log kayıtları otomatik olarak oluşturulur ve işlenir. Çıktı olarak:
1. Tüm log kayıtları görüntülenir
2. Öncelik seviyesi 3 (INFO) olan kayıtlar filtrelenir

## Veri Yapıları

### SyslogEntry
Her bir log kaydı için temel veri yapısı:
- timestamp: Zaman damgası (26 karakter)
- hostname: Sunucu adı (64 karakter)
- process: Süreç adı (64 karakter)
- priority: Öncelik seviyesi (integer)
- message: Log mesajı (512 karakter)

### LinkedList
Çift yönlü bağlı liste yapısı:
- head: İlk düğüm
- tail: Son düğüm
- size: Liste boyutu

## Fonksiyonlar

### Ana Fonksiyonlar
- `initializeList()`: Yeni bir bağlı liste oluşturur
- `addEntry()`: Listeye yeni bir kayıt ekler
- `parseSyslogLine()`: Syslog satırını ayrıştırır
- `displayList()`: Tüm kayıtları görüntüler
- `filterByPriority()`: Belirli öncelik seviyesindeki kayıtları filtreler
- `freeList()`: Belleği temizler

## Örnek Çıktı

```
Syslog Kayitlari:
----------------------------------------
Zaman: 2024-02-22 10:15:30
Hostname: win-pc
Surec: system[1234]
Oncelik: 3
Mesaj: System baslatildi
----------------------------------------
[Diğer kayıtlar...]
```

## Sınırlamalar

- Sabit boyutlu karakter dizileri kullanılmaktadır
- Tek bir öncelik seviyesi filtrelemesi yapılabilir
- Basit syslog satır ayrıştırma kullanılmaktadır

## Gelecek Geliştirmeler

- Dinamik bellek yönetimi iyileştirmeleri
- Gelişmiş filtreleme seçenekleri
- Dosyadan log okuma desteği
- Gerçek zamanlı log izleme
- Çoklu öncelik seviyesi filtreleme

## Hata Ayıklama

Bellek sızıntılarını kontrol etmek için Valgrind kullanılabilir:

```bash
valgrind --leak-check=full ./syslog_manager
```

## Lisans

Bu proje açık kaynak olarak MIT lisansı altında dağıtılmaktadır.

## İletişim

Sorularınız ve önerileriniz için bir Issue açabilirsiniz.
