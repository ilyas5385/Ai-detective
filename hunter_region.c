#include "hunter_region.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// 🔧 تهيئة HUNTER Region
void hunter_init(HunterRegion* hunter, TunnelSystem* tunnel_system) {
    memset(hunter, 0, sizeof(HunterRegion));
    hunter->tunnel_system = tunnel_system;
    hunter->active = true;
    
    // إنشاء Tunnels للخلايا
    hunter->search_cell.input_tunnel = tunnel_create(tunnel_system, 
                                                      REGION_PERCEPTION, 
                                                      REGION_HUNTER);
    hunter->search_cell.output_tunnel = tunnel_create(tunnel_system, 
                                                       REGION_HUNTER, 
                                                       REGION_REASONING);
    
    hunter->pattern_cell.input_tunnel = hunter->search_cell.output_tunnel;
    hunter->pattern_cell.output_tunnel = tunnel_create(tunnel_system,
                                                        REGION_HUNTER,
                                                        REGION_REASONING);
    
    hunter->entity_cell.input_tunnel = hunter->pattern_cell.output_tunnel;
    hunter->entity_cell.output_tunnel = tunnel_create(tunnel_system,
                                                       REGION_HUNTER,
                                                       REGION_MEMORY);
    
    hunter->anomaly_cell.anomaly_threshold = 0.3;
    hunter->anomaly_cell.input_tunnel = hunter->search_cell.input_tunnel;
    hunter->anomaly_cell.output_tunnel = tunnel_create(tunnel_system,
                                                        REGION_HUNTER,
                                                        REGION_CONSCIOUSNESS);
    
    printf("🦅 HUNTER Region initialized with %u cells\n", NUM_HUNTER_CELLS);
}

// 🔍 Cell 1: معالجة البحث عن المصادر
void search_source_process(SearchSourceCell* cell, const Evidence* evidence) {
    if (!cell || !evidence) return;
    
    // إضافة الدليل إلى المجموعة
    if (cell->num_evidence < MAX_EVIDENCE) {
        memcpy(&cell->evidence_pool[cell->num_evidence], evidence, sizeof(Evidence));
        cell->num_evidence++;
        
        printf("🔍 [SearchSource] Added evidence: %s (source: %s, weight: %.2f)\n",
               evidence->id, evidence->source, evidence->weight);
        
        // إرسال رسالة عبر Tunnel
        TunnelMessage msg = {0};
        strncpy(msg.evidence_id, evidence->id, MAX_EVIDENCE_ID - 1);
        msg.weight = evidence->weight;
        strncpy(msg.type, evidence->type, MAX_TYPE_LEN - 1);
        strncpy(msg.source, evidence->source, MAX_SOURCE_LEN - 1);
        msg.timestamp = evidence->timestamp;
        msg.priority = (uint8_t)(evidence->weight * 255);
        msg.sender_id = REGION_HUNTER;
        msg.receiver_id = REGION_REASONING;
        
        tunnel_send(cell->output_tunnel, &msg);
    }
}

// 🧬 Cell 2: كشف الأنماط
void pattern_detection_process(PatternDetectionCell* cell) {
    if (!cell || cell->num_patterns >= MAX_PATTERNS) return;
    
    // محاكاة كشف نمط
    Pattern new_pattern;
    new_pattern.id = cell->num_patterns;
    snprintf(new_pattern.description, 128, 
             "Pattern_%u: Time-Location correlation", new_pattern.id);
    new_pattern.num_evidence = 0;
    new_pattern.confidence = 0.75 + (rand() % 25) / 100.0;
    strncpy(new_pattern.pattern_type, "temporal_spatial", 31);
    
    cell->patterns[cell->num_patterns++] = new_pattern;
    
    printf("🧬 [PatternDetection] Discovered pattern: %s (confidence: %.2f)\n",
           new_pattern.description, new_pattern.confidence);
    
    // إرسال النمط عبر Tunnel
    TunnelMessage msg = {0};
    snprintf(msg.evidence_id, MAX_EVIDENCE_ID, "PATTERN_%u", new_pattern.id);
    msg.weight = new_pattern.confidence;
    strncpy(msg.type, "pattern", MAX_TYPE_LEN - 1);
    msg.timestamp = time(NULL);
    msg.priority = 200;
    
    tunnel_send(cell->output_tunnel, &msg);
}

// 🎯 Cell 3: مطابقة الكيانات
void entity_matching_process(EntityMatchingCell* cell) {
    if (!cell) return;
    
    // محاكاة اكتشاف كيان مشتبه به
    if (cell->num_entities < MAX_ENTITIES) {
        Entity new_entity;
        new_entity.id = cell->num_entities;
        snprintf(new_entity.name, 64, "Suspect_%u", new_entity.id);
        strncpy(new_entity.role, "Unknown", 31);
        new_entity.num_evidence = 0;
        new_entity.suspicion_level = 0.5 + (rand() % 50) / 100.0;
        
        cell->entities[cell->num_entities++] = new_entity;
        
        printf("🎯 [EntityMatching] Identified entity: %s (suspicion: %.2f)\n",
               new_entity.name, new_entity.suspicion_level);
        
        // إرسال الكيان عبر Tunnel
        TunnelMessage msg = {0};
        snprintf(msg.evidence_id, MAX_EVIDENCE_ID, "ENTITY_%u", new_entity.id);
        msg.weight = new_entity.suspicion_level;
        strncpy(msg.type, "entity", MAX_TYPE_LEN - 1);
        msg.timestamp = time(NULL);
        msg.priority = 180;
        
        tunnel_send(cell->output_tunnel, &msg);
    }
}

// ⚠️ Cell 4: كشف الشذوذ
void anomaly_detector_process(AnomalyDetectorCell* cell, const Evidence* evidence) {
    if (!cell || !evidence) return;
    
    // حساب درجة الشذوذ بناءً على الوزن والمصدر
    double anomaly_score = 0.0;
    
    // دليل بوزن منخفض جداً أو عالي جداً
    if (evidence->weight < 0.1 || evidence->weight > 0.95) {
        anomaly_score += 0.4;
    }
    
    // مصدر غير معروف
    if (strstr(evidence->source, "unknown") != NULL) {
        anomaly_score += 0.3;
    }
    
    // نوع غريب
    if (strstr(evidence->type, "anomalous") != NULL) {
        anomaly_score += 0.3;
    }
    
    if (anomaly_score > cell->anomaly_threshold) {
        cell->anomalies_detected++;
        
        printf("⚠️  [AnomalyDetector] ANOMALY DETECTED: %s (score: %.2f)\n",
               evidence->id, anomaly_score);
        
        // إرسال تحذير عبر Tunnel
        TunnelMessage msg = {0};
        strncpy(msg.evidence_id, evidence->id, MAX_EVIDENCE_ID - 1);
        msg.weight = anomaly_score;
        strncpy(msg.type, "anomaly_alert", MAX_TYPE_LEN - 1);
        msg.timestamp = time(NULL);
        msg.priority = 255; // أعلى أولوية!
        msg.sender_id = REGION_HUNTER;
        msg.receiver_id = REGION_CONSCIOUSNESS;
        
        tunnel_send(cell->output_tunnel, &msg);
    }
}

// ⚡ تشغيل دورة معالجة HUNTER كاملة
void hunter_process_cycle(HunterRegion* hunter) {
    if (!hunter || !hunter->active) return;
    
    printf("\n⚡ HUNTER Processing Cycle %u\n", hunter->total_processed);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    // كشف أنماط جديدة
    if (rand() % 3 == 0) {
        pattern_detection_process(&hunter->pattern_cell);
    }
    
    // مطابقة كيانات
    if (rand() % 4 == 0) {
        entity_matching_process(&hunter->entity_cell);
    }
    
    hunter->total_processed++;
}

// 📊 إحصائيات HUNTER
void hunter_stats(const HunterRegion* hunter) {
    if (!hunter) return;
    
    printf("\n📊 HUNTER REGION STATISTICS\n");
    printf("═══════════════════════════════════════\n");
    printf("🔍 Search Source Cell:\n");
    printf("   Evidence collected: %u / %u\n", 
           hunter->search_cell.num_evidence, MAX_EVIDENCE);
    
    printf("\n🧬 Pattern Detection Cell:\n");
    printf("   Patterns discovered: %u / %u\n", 
           hunter->pattern_cell.num_patterns, MAX_PATTERNS);
    
    printf("\n🎯 Entity Matching Cell:\n");
    printf("   Entities identified: %u / %u\n", 
           hunter->entity_cell.num_entities, MAX_ENTITIES);
    
    printf("\n⚠️  Anomaly Detector Cell:\n");
    printf("   Anomalies detected: %u\n", 
           hunter->anomaly_cell.anomalies_detected);
    printf("   Threshold: %.2f\n", hunter->anomaly_cell.anomaly_threshold);
    
    printf("\n📈 Total cycles processed: %u\n", hunter->total_processed);
    printf("═══════════════════════════════════════\n");
}
