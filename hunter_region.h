#ifndef HUNTER_REGION_H
#define HUNTER_REGION_H

#include "tunnel_system.h"
#include <stdbool.h>

#define MAX_EVIDENCE 128
#define MAX_PATTERNS 64
#define MAX_ENTITIES 32

// 🔍 Evidence Structure
typedef struct {
    char id[MAX_EVIDENCE_ID];
    char content[256];
    double weight;
    char type[MAX_TYPE_LEN];
    char source[MAX_SOURCE_LEN];
    uint64_t timestamp;
    bool verified;
} Evidence;

// 🧩 Pattern Structure
typedef struct {
    uint32_t id;
    char description[128];
    uint32_t evidence_ids[16];
    uint32_t num_evidence;
    double confidence;
    char pattern_type[32];
} Pattern;

// 👤 Entity Structure
typedef struct {
    uint32_t id;
    char name[64];
    char role[32];
    uint32_t related_evidence[16];
    uint32_t num_evidence;
    double suspicion_level;
} Entity;

// 🔬 خلية البحث عن المصادر
typedef struct {
    uint32_t cell_id;
    Evidence evidence_pool[MAX_EVIDENCE];
    uint32_t num_evidence;
    Tunnel* input_tunnel;
    Tunnel* output_tunnel;
} SearchSourceCell;

// 🧬 خلية كشف الأنماط
typedef struct {
    uint32_t cell_id;
    Pattern patterns[MAX_PATTERNS];
    uint32_t num_patterns;
    Tunnel* input_tunnel;
    Tunnel* output_tunnel;
} PatternDetectionCell;

// 🎯 خلية مطابقة الكيانات
typedef struct {
    uint32_t cell_id;
    Entity entities[MAX_ENTITIES];
    uint32_t num_entities;
    Tunnel* input_tunnel;
    Tunnel* output_tunnel;
} EntityMatchingCell;

// ⚠️ خلية كشف الشذوذ
typedef struct {
    uint32_t cell_id;
    double anomaly_threshold;
    uint32_t anomalies_detected;
    Tunnel* input_tunnel;
    Tunnel* output_tunnel;
} AnomalyDetectorCell;

// 🦅 HUNTER Region (يحتوي جميع الخلايا)
typedef struct {
    SearchSourceCell search_cell;
    PatternDetectionCell pattern_cell;
    EntityMatchingCell entity_cell;
    AnomalyDetectorCell anomaly_cell;
    
    TunnelSystem* tunnel_system;
    uint32_t total_processed;
    bool active;
} HunterRegion;

// 🔧 تهيئة HUNTER Region
void hunter_init(HunterRegion* hunter, TunnelSystem* tunnel_system);

// 🔍 Cell 1: معالجة البحث عن المصادر
void search_source_process(SearchSourceCell* cell, const Evidence* evidence);

// 🧬 Cell 2: كشف الأنماط
void pattern_detection_process(PatternDetectionCell* cell);

// 🎯 Cell 3: مطابقة الكيانات
void entity_matching_process(EntityMatchingCell* cell);

// ⚠️ Cell 4: كشف الشذوذ
void anomaly_detector_process(AnomalyDetectorCell* cell, const Evidence* evidence);

// ⚡ تشغيل دورة معالجة HUNTER كاملة
void hunter_process_cycle(HunterRegion* hunter);

// 📊 إحصائيات HUNTER
void hunter_stats(const HunterRegion* hunter);

#endif // HUNTER_REGION_H
