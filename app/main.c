#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Syslog girisi için yapi
typedef struct {
    char timestamp[26];
    char hostname[64];
    char process[64];
    int priority;
    char message[512];
} SyslogEntry;

// Çift yönlü bagli liste dügümü
typedef struct Node {
    SyslogEntry data;
    struct Node* next;
    struct Node* prev;
} Node;

// Bagli liste yapisi
typedef struct {
    Node* head;
    Node* tail;
    int size;
} LinkedList;

// Bagli liste baslatma
LinkedList* initializeList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Yeni dügüm olusturma
Node* createNode(SyslogEntry entry) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = entry;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Listeye yeni giris ekleme (sona ekleme)
void addEntry(LinkedList* list, SyslogEntry entry) {
    Node* newNode = createNode(entry);
    
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->size++;
}

// Örnek syslog satirini parse etme
SyslogEntry parseSyslogLine(const char* line) {
    SyslogEntry entry;
    memset(&entry, 0, sizeof(SyslogEntry));
    
    // Basit bir parsing örnegi
    // Format: timestamp hostname process[pid]: message
    sscanf(line, "%25[^] ] %63s %63[^:]: %511[^\n]",
           entry.timestamp,
           entry.hostname,
           entry.process,
           entry.message);
    
    // Örnek öncelik atama (gerçek uygulamada daha karmasik olabilir)
    entry.priority = 3; // INFO level
    
    return entry;
}

// Listeyi görüntüleme
void displayList(LinkedList* list) {
    Node* current = list->head;
    printf("\nSyslog Kayitlari:\n");
    printf("----------------------------------------\n");
    
    while (current != NULL) {
        printf("Zaman: %s\n", current->data.timestamp);
        printf("Hostname: %s\n", current->data.hostname);
        printf("Surec: %s\n", current->data.process);
        printf("Oncelik: %d\n", current->data.priority);
        printf("Mesaj: %s\n", current->data.message);
        printf("----------------------------------------\n");
        current = current->next;
    }
}

// Öncelige göre filtreleme
void filterByPriority(LinkedList* list, int priority) {
    Node* current = list->head;
    printf("\nOncelik %d olan kayitlar:\n", priority);
    printf("----------------------------------------\n");
    
    while (current != NULL) {
        if (current->data.priority == priority) {
            printf("Zaman: %s\n", current->data.timestamp);
            printf("Mesaj: %s\n", current->data.message);
            printf("----------------------------------------\n");
        }
        current = current->next;
    }
}

// Bellegi temizleme
void freeList(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

int main() {
    LinkedList* syslogList = initializeList();
    
    // Örnek syslog girisleri
    const char* sampleLogs[] = {
        "2024-02-22 10:15:30 win-pc system[1234]: System baslatildi",
        "2024-02-22 10:15:35 win-pc service[5678]: Servis baslatildi",
        "2024-02-22 10:15:40 win-pc app[9012]: Uygulama hatasi"
    };
    
    // Örnek kayitlari ekleme
    for (int i = 0; i < 3; i++) {
        SyslogEntry entry = parseSyslogLine(sampleLogs[i]);
        addEntry(syslogList, entry);
    }
    
    // Tüm kayitlari gösterme
    displayList(syslogList);
    
    // Öncelige göre filtreleme
    filterByPriority(syslogList, 3);
    
    // Bellegi temizleme
    freeList(syslogList);
    
    return 0;
}
