#ifndef TUNNEL_SYSTEM_H
#define TUNNEL_SYSTEM_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_HYPOTHESES 8
#define MAX_EVIDENCE_ID 32
#define MAX_TYPE_LEN 32
#define MAX_SOURCE_LEN 64
#define MAX_TUNNELS 16
#define TUNNEL_QUEUE_SIZE 256

// 📡 هيكل رسالة Tunnel
typedef struct {
    char evidence_id[MAX_EVIDENCE_ID];
    double weight;                          // قوة الدليل (0-1)
    char type[MAX_TYPE_LEN];                // نوع الدليل
    char source[MAX_SOURCE_LEN];            // المصدر
    uint32_t hypotheses_ids[MAX_HYPOTHESES]; // الفرضيات المرتبطة
    double updated_probability[MAX_HYPOTHESES]; // الاحتمالات المحدثة
    uint64_t timestamp;                     // وقت الرسالة
    uint8_t priority;                       // الأولوية (0-255)
    uint32_t sender_id;                     // معرف المرسل
    uint32_t receiver_id;                   // معرف المستقبل
} TunnelMessage;

// 🔗 هيكل Tunnel (قناة اتصال بين خليتين)
typedef struct {
    uint32_t id;
    uint32_t from_region;
    uint32_t to_region;
    TunnelMessage queue[TUNNEL_QUEUE_SIZE];
    uint32_t head;
    uint32_t tail;
    uint32_t count;
    bool active;
    double bandwidth_usage;  // استخدام النطاق الترددي
} Tunnel;

// 🧠 أنواع المناطق (Regions)
typedef enum {
    REGION_CONSCIOUSNESS = 0,
    REGION_PERCEPTION,
    REGION_REASONING,
    REGION_HUNTER,
    REGION_MEMORY,
    REGION_IO,
    NUM_REGIONS
} RegionType;

// 🔬 أنواع خلايا HUNTER
typedef enum {
    HUNTER_CELL_SEARCH_SOURCE = 0,
    HUNTER_CELL_PATTERN_DETECTION,
    HUNTER_CELL_ENTITY_MATCHING,
    HUNTER_CELL_ANOMALY_DETECTOR,
    NUM_HUNTER_CELLS
} HunterCellType;

// 🌐 نظام إدارة Tunnels
typedef struct {
    Tunnel tunnels[MAX_TUNNELS];
    uint32_t num_tunnels;
    uint64_t total_messages_sent;
    uint64_t total_messages_received;
} TunnelSystem;

// 📤 إرسال رسالة عبر Tunnel
bool tunnel_send(Tunnel* tunnel, const TunnelMessage* msg);

// 📥 استقبال رسالة من Tunnel
bool tunnel_receive(Tunnel* tunnel, TunnelMessage* msg);

// 🔧 إنشاء Tunnel جديد
Tunnel* tunnel_create(TunnelSystem* system, uint32_t from, uint32_t to);

// 📊 إحصائيات Tunnel
void tunnel_stats(const Tunnel* tunnel);

// 🧹 تنظيف النظام
void tunnel_system_cleanup(TunnelSystem* system);

#endif // TUNNEL_SYSTEM_H
