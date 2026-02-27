#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "tunnel_system.h"
#include "hunter_region.h"
#include "reasoning_region.h"

// 🎭 قضية معقدة: التلاعب بالبورصة (Stock Market Manipulation)
// الهدف: الوصول إلى المتلاعب الحقيقي "Marcus Chen"

typedef struct {
    const char* name;
    const char* description;
    Evidence evidence[15];
    int num_evidence;
    const char* actual_culprit;  // الجاني الحقيقي
} ComplexCase;

// 🎨 إنشاء قضية معقدة مع كيان مستهدف
ComplexCase create_stock_manipulation_case() {
    ComplexCase case_data;
    case_data.name = "TechCorp Stock Manipulation Investigation";
    case_data.description = "Suspicious trading patterns detected before major TechCorp announcement";
    case_data.num_evidence = 12;
    case_data.actual_culprit = "Marcus Chen (Senior Trader)";
    
    // ═══════════════════════════════════════════════════════════
    // الأدلة التي تشير إلى Marcus Chen بشكل تدريجي
    // ═══════════════════════════════════════════════════════════
    
    // دليل 1: نشاط تداول غير عادي
    Evidence e1 = {0};
    strcpy(e1.id, "EVIDENCE_001");
    strcpy(e1.content, "Unusual trading activity 3 days before announcement");
    strcpy(e1.type, "trading_pattern");
    strcpy(e1.source, "SEC Trading Monitor");
    e1.weight = 0.75;
    e1.timestamp = time(NULL) - (3 * 86400);
    e1.verified = true;
    case_data.evidence[0] = e1;
    
    // دليل 2: حساب تداول مشبوه
    Evidence e2 = {0};
    strcpy(e2.id, "EVIDENCE_002");
    strcpy(e2.content, "Offshore account 'MC_Investments_2024' made large purchase");
    strcpy(e2.type, "financial");
    strcpy(e2.source, "Bank Records");
    e2.weight = 0.82;
    e2.timestamp = time(NULL) - (3 * 86400) + 3600;
    e2.verified = true;
    case_data.evidence[1] = e2;
    
    // دليل 3: اجتماع مشبوه
    Evidence e3 = {0};
    strcpy(e3.id, "EVIDENCE_003");
    strcpy(e3.content, "Meeting between senior trader and CEO assistant at luxury hotel");
    strcpy(e3.type, "surveillance");
    strcpy(e3.source, "Hotel Security Camera");
    e3.weight = 0.65;
    e3.timestamp = time(NULL) - (4 * 86400);
    e3.verified = true;
    case_data.evidence[2] = e3;
    
    // دليل 4: مكالمة هاتفية مشفرة
    Evidence e4 = {0};
    strcpy(e4.id, "EVIDENCE_004");
    strcpy(e4.content, "Encrypted call from phone registered to M.Chen discussing 'the big move'");
    strcpy(e4.type, "communication");
    strcpy(e4.source, "Phone Tap Warrant");
    e4.weight = 0.88;
    e4.timestamp = time(NULL) - (2 * 86400);
    e4.verified = true;
    case_data.evidence[3] = e4;
    
    // دليل 5: وصول غير مصرح به
    Evidence e5 = {0};
    strcpy(e5.id, "EVIDENCE_005");
    strcpy(e5.content, "Badge swipe: Marcus Chen accessed executive floor at 11 PM");
    strcpy(e5.type, "digital");
    strcpy(e5.source, "Building Access Control");
    e5.weight = 0.79;
    e5.timestamp = time(NULL) - (4 * 86400) + 7200;
    e5.verified = true;
    case_data.evidence[4] = e5;
    
    // دليل 6: سجل حاسوب
    Evidence e6 = {0};
    strcpy(e6.id, "EVIDENCE_006");
    strcpy(e6.content, "Computer logs show Marcus Chen's workstation accessed confidential files");
    strcpy(e6.type, "digital");
    strcpy(e6.source, "IT Security Logs");
    e6.weight = 0.91;
    e6.timestamp = time(NULL) - (4 * 86400) + 8000;
    e6.verified = true;
    case_data.evidence[5] = e6;
    
    // دليل 7: شاهد عيان
    Evidence e7 = {0};
    strcpy(e7.id, "EVIDENCE_007");
    strcpy(e7.content, "Janitor reports seeing Mr. Chen printing documents late at night");
    strcpy(e7.type, "testimonial");
    strcpy(e7.source, "Witness Statement");
    e7.weight = 0.58;
    e7.timestamp = time(NULL) - (3 * 86400);
    e7.verified = false;
    case_data.evidence[6] = e7;
    
    // دليل 8: سجل جنائي سابق
    Evidence e8 = {0};
    strcpy(e8.id, "EVIDENCE_008");
    strcpy(e8.content, "Marcus Chen has prior SEC investigation (2019) - no charges filed");
    strcpy(e8.type, "background");
    strcpy(e8.source, "Criminal Database");
    e8.weight = 0.45;
    e8.timestamp = time(NULL) - (5 * 86400);
    e8.verified = true;
    case_data.evidence[7] = e8;
    
    // دليل 9: تحويلات مالية
    Evidence e9 = {0};
    strcpy(e9.id, "EVIDENCE_009");
    strcpy(e9.content, "Wire transfer of $50K from MC_Investments to unknown recipient");
    strcpy(e9.type, "financial");
    strcpy(e9.source, "Bank Transaction Records");
    e9.weight = 0.84;
    e9.timestamp = time(NULL) - (2 * 86400);
    e9.verified = true;
    case_data.evidence[8] = e9;
    
    // دليل 10: دليل مُضلل (Red Herring)
    Evidence e10 = {0};
    strcpy(e10.id, "EVIDENCE_010");
    strcpy(e10.content, "Anonymous tip pointing to junior analyst 'Sarah Kim'");
    strcpy(e10.type, "anomalous");
    strcpy(e10.source, "unknown");
    e10.weight = 0.12;
    e10.timestamp = time(NULL) - (1 * 86400);
    e10.verified = false;
    case_data.evidence[9] = e10;
    
    // دليل 11: بريد إلكتروني مشبوه
    Evidence e11 = {0};
    strcpy(e11.id, "EVIDENCE_011");
    strcpy(e11.content, "Email from Marcus Chen to external contact: 'package is ready'");
    strcpy(e11.type, "communication");
    strcpy(e11.source, "Email Server Logs");
    e11.weight = 0.77;
    e11.timestamp = time(NULL) - (2 * 86400) + 3600;
    e11.verified = true;
    case_data.evidence[10] = e11;
    
    // دليل 12: تحليل DNA (دليل قوي جداً)
    Evidence e12 = {0};
    strcpy(e12.id, "EVIDENCE_012");
    strcpy(e12.content, "Fingerprints on confidential documents match Marcus Chen");
    strcpy(e12.type, "physical");
    strcpy(e12.source, "Forensics Lab");
    e12.weight = 0.95;
    e12.timestamp = time(NULL) - (1 * 86400);
    e12.verified = true;
    case_data.evidence[11] = e12;
    
    return case_data;
}

// 🎯 تحليل متقدم: ربط الأدلة بالكيان المستهدف
void advanced_entity_matching(EntityMatchingCell* cell, const Evidence* evidence, 
                             const char* target_name) {
    if (!cell || !evidence) return;
    
    // تحليل محتوى الدليل للبحث عن الاسم أو الأحرف الأولى
    bool name_match = false;
    bool initials_match = false;
    bool indirect_match = false;
    
    // بحث مباشر عن الاسم
    if (strstr(evidence->content, "Marcus Chen") != NULL ||
        strstr(evidence->content, "Marcus") != NULL ||
        strstr(evidence->content, "Chen") != NULL) {
        name_match = true;
    }
    
    // بحث عن الأحرف الأولى MC
    if (strstr(evidence->content, "M.Chen") != NULL ||
        strstr(evidence->content, "MC_") != NULL ||
        strstr(evidence->content, "M Chen") != NULL) {
        initials_match = true;
    }
    
    // بحث غير مباشر (senior trader, workstation, etc.)
    if (strstr(evidence->content, "senior trader") != NULL ||
        strstr(evidence->content, "Mr. Chen") != NULL) {
        indirect_match = true;
    }
    
    // حساب مستوى الثقة بالربط
    double match_confidence = 0.0;
    if (name_match) match_confidence += 0.9;
    if (initials_match) match_confidence += 0.7;
    if (indirect_match) match_confidence += 0.5;
    
    // تطبيع الثقة
    match_confidence = fmin(1.0, match_confidence);
    
    // إنشاء أو تحديث الكيان
    Entity* target_entity = NULL;
    for (uint32_t i = 0; i < cell->num_entities; i++) {
        if (strcmp(cell->entities[i].name, target_name) == 0) {
            target_entity = &cell->entities[i];
            break;
        }
    }
    
    if (!target_entity && cell->num_entities < MAX_ENTITIES) {
        target_entity = &cell->entities[cell->num_entities];
        target_entity->id = cell->num_entities;
        strncpy(target_entity->name, target_name, 63);
        strcpy(target_entity->role, "Senior Trader");
        target_entity->num_evidence = 0;
        target_entity->suspicion_level = 0.0;
        cell->num_entities++;
        
        printf("🎯 [EntityMatching] NEW ENTITY CREATED: %s\n", target_name);
    }
    
    if (target_entity && match_confidence > 0.3) {
        // إضافة الدليل للكيان
        if (target_entity->num_evidence < 16) {
            target_entity->related_evidence[target_entity->num_evidence++] = 
                atoi(evidence->id + 9);  // استخراج الرقم من EVIDENCE_XXX
        }
        
        // تحديث مستوى الشبهة
        double evidence_impact = evidence->weight * match_confidence;
        target_entity->suspicion_level += evidence_impact * 0.15;
        target_entity->suspicion_level = fmin(1.0, target_entity->suspicion_level);
        
        printf("   🔗 Evidence %s LINKED to %s\n", evidence->id, target_name);
        printf("   📊 Match confidence: %.2f | Impact: %.2f\n", 
               match_confidence, evidence_impact);
        printf("   📈 Updated suspicion level: %.2f → %.2f\n",
               target_entity->suspicion_level - evidence_impact * 0.15,
               target_entity->suspicion_level);
    }
}

// 🧬 تحليل متقدم للأنماط
void advanced_pattern_detection(PatternDetectionCell* cell, 
                               const Evidence evidence[], int num_evidence) {
    printf("\n🧬 [ADVANCED PATTERN DETECTION]\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    // نمط 1: تسلسل زمني
    printf("📅 Temporal Pattern Analysis:\n");
    int temporal_cluster = 0;
    for (int i = 0; i < num_evidence - 1; i++) {
        time_t diff = labs(evidence[i].timestamp - evidence[i+1].timestamp);
        if (diff < 86400) {  // في نفس اليوم
            temporal_cluster++;
        }
    }
    
    if (temporal_cluster > 3) {
        Pattern temporal_pattern;
        temporal_pattern.id = cell->num_patterns;
        sprintf(temporal_pattern.description, 
                "STRONG temporal clustering: %d events within 24h window", 
                temporal_cluster);
        temporal_pattern.confidence = 0.85;
        strcpy(temporal_pattern.pattern_type, "temporal_sequence");
        
        if (cell->num_patterns < MAX_PATTERNS) {
            cell->patterns[cell->num_patterns++] = temporal_pattern;
            printf("   ✅ Pattern: %s (confidence: %.2f)\n", 
                   temporal_pattern.description, temporal_pattern.confidence);
        }
    }
    
    // نمط 2: تكرار المصادر
    printf("\n📋 Source Pattern Analysis:\n");
    int digital_count = 0, financial_count = 0, communication_count = 0;
    
    for (int i = 0; i < num_evidence; i++) {
        if (strcmp(evidence[i].type, "digital") == 0) digital_count++;
        if (strcmp(evidence[i].type, "financial") == 0) financial_count++;
        if (strcmp(evidence[i].type, "communication") == 0) communication_count++;
    }
    
    printf("   Digital evidence: %d\n", digital_count);
    printf("   Financial evidence: %d\n", financial_count);
    printf("   Communication evidence: %d\n", communication_count);
    
    if (digital_count >= 2 && financial_count >= 2) {
        Pattern insider_pattern;
        insider_pattern.id = cell->num_patterns;
        sprintf(insider_pattern.description,
                "INSIDER THREAT signature: %d digital + %d financial traces",
                digital_count, financial_count);
        insider_pattern.confidence = 0.92;
        strcpy(insider_pattern.pattern_type, "insider_threat");
        
        if (cell->num_patterns < MAX_PATTERNS) {
            cell->patterns[cell->num_patterns++] = insider_pattern;
            printf("   ⚠️  Pattern: %s (confidence: %.2f)\n",
                   insider_pattern.description, insider_pattern.confidence);
        }
    }
    
    // نمط 3: سلسلة السلوك المشبوه
    printf("\n🔗 Behavioral Chain Analysis:\n");
    bool has_access = false, has_transaction = false, has_communication = false;
    
    for (int i = 0; i < num_evidence; i++) {
        if (strstr(evidence[i].content, "accessed") != NULL) has_access = true;
        if (strstr(evidence[i].content, "transfer") != NULL || 
            strstr(evidence[i].content, "purchase") != NULL) has_transaction = true;
        if (strcmp(evidence[i].type, "communication") == 0) has_communication = true;
    }
    
    if (has_access && has_transaction && has_communication) {
        Pattern behavior_chain;
        behavior_chain.id = cell->num_patterns;
        strcpy(behavior_chain.description, 
               "Complete behavior chain: Access → Communication → Transaction");
        behavior_chain.confidence = 0.88;
        strcpy(behavior_chain.pattern_type, "behavior_chain");
        
        if (cell->num_patterns < MAX_PATTERNS) {
            cell->patterns[cell->num_patterns++] = behavior_chain;
            printf("   🎯 Pattern: %s (confidence: %.2f)\n",
                   behavior_chain.description, behavior_chain.confidence);
        }
    }
}

// 🎯 تشغيل المحقق الاصطناعي على القضية المعقدة
void run_advanced_investigation(ComplexCase* case_data) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║     🕵️  ADVANCED DETECTIVE AI - COMPLEX CASE SOLVER 🕵️      ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("📋 CASE: %s\n", case_data->name);
    printf("📝 Description: %s\n", case_data->description);
    printf("📊 Total Evidence: %d\n", case_data->num_evidence);
    printf("🎯 TARGET ENTITY: %s\n", case_data->actual_culprit);
    printf("\n");
    
    // تهيئة النظام
    TunnelSystem tunnel_system = {0};
    HunterRegion hunter;
    ReasoningRegion reasoning;
    
    hunter_init(&hunter, &tunnel_system);
    reasoning_init(&reasoning, &tunnel_system);
    
    // توليد فرضيات متعددة
    printf("\n💡 GENERATING HYPOTHESES\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    reasoning_generate_hypothesis(&reasoning,
        "H1: Marcus Chen (Senior Trader) - Insider Trading",
        0.30);
    
    reasoning_generate_hypothesis(&reasoning,
        "H2: Sarah Kim (Junior Analyst) - Scapegoat Theory",
        0.15);
    
    reasoning_generate_hypothesis(&reasoning,
        "H3: External Hacker - Sophisticated Breach",
        0.25);
    
    reasoning_generate_hypothesis(&reasoning,
        "H4: CEO Assistant - Information Leak",
        0.20);
    
    reasoning_generate_hypothesis(&reasoning,
        "H5: Organized Crime Syndicate - Complex Scheme",
        0.10);
    
    // معالجة الأدلة واحداً تلو الآخر
    printf("\n\n🔍 PROCESSING EVIDENCE CHAIN\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    for (int i = 0; i < case_data->num_evidence; i++) {
        Evidence* e = &case_data->evidence[i];
        
        printf("\n┌─────────────────────────────────────────────────────┐\n");
        printf("│ Processing Evidence %d/%d                            \n", i + 1, case_data->num_evidence);
        printf("└─────────────────────────────────────────────────────┘\n");
        printf("ID: %s\n", e->id);
        printf("Content: %s\n", e->content);
        printf("Type: %s | Source: %s | Weight: %.2f\n", e->type, e->source, e->weight);
        printf("\n");
        
        // Cell 1: Search Source
        search_source_process(&hunter.search_cell, e);
        
        // Cell 3: Advanced Entity Matching
        advanced_entity_matching(&hunter.entity_cell, e, "Marcus Chen");
        
        // Cell 4: Anomaly Detection
        anomaly_detector_process(&hunter.anomaly_cell, e);
        
        // معالجة في REASONING
        reasoning_process_cycle(&reasoning);
        
        printf("\n");
    }
    
    // تحليل الأنماط المتقدم
    advanced_pattern_detection(&hunter.pattern_cell, 
                               case_data->evidence, 
                               case_data->num_evidence);
    
    // إعادة حساب الفرضيات
    printf("\n");
    reasoning_recalculate_all(&reasoning);
    
    // تحليل نهائي للكيانات
    printf("\n\n🎯 ENTITY ANALYSIS RESULTS\n");
    printf("═══════════════════════════════════════════════════════════\n");
    
    for (uint32_t i = 0; i < hunter.entity_cell.num_entities; i++) {
        Entity* entity = &hunter.entity_cell.entities[i];
        
        printf("\n👤 Entity %u: %s\n", entity->id + 1, entity->name);
        printf("   Role: %s\n", entity->role);
        printf("   Suspicion Level: %.2f%%\n", entity->suspicion_level * 100);
        printf("   Linked Evidence: %u pieces\n", entity->num_evidence);
        
        // مؤشر مرئي
        int bar_length = (int)(entity->suspicion_level * 50);
        printf("   [");
        for (int j = 0; j < 50; j++) {
            if (j < bar_length) printf("█");
            else printf("░");
        }
        printf("]\n");
        
        // تقييم
        if (entity->suspicion_level > 0.7) {
            printf("   🚨 VERDICT: HIGH PROBABILITY SUSPECT\n");
        } else if (entity->suspicion_level > 0.4) {
            printf("   ⚠️  VERDICT: PERSON OF INTEREST\n");
        } else {
            printf("   ✅ VERDICT: LOW SUSPICION\n");
        }
    }
    
    // اختيار أفضل فرضية
    printf("\n\n🏆 FINAL INVESTIGATION CONCLUSION\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    Hypothesis* best = reasoning_select_best_hypothesis(&reasoning);
    if (best) {
        printf("\n🎯 MOST PROBABLE HYPOTHESIS:\n");
        printf("   %s\n", best->description);
        printf("   Posterior Probability: %.1f%%\n", best->posterior_probability * 100);
        printf("   Supporting Evidence: %u\n", best->num_supporting);
        printf("   Contradicting Evidence: %u\n", best->num_contradicting);
        
        // مقارنة مع الجاني الحقيقي
        printf("\n✅ ACTUAL CULPRIT: %s\n", case_data->actual_culprit);
        
        if (strstr(best->description, "Marcus Chen") != NULL) {
            printf("\n🎊 ═══════════════════════════════════════════ 🎊\n");
            printf("   ✅ ✅ ✅  INVESTIGATION SUCCESSFUL!  ✅ ✅ ✅\n");
            printf("   🎊 ═══════════════════════════════════════════ 🎊\n");
            printf("\n   The AI correctly identified the culprit!\n");
        } else {
            printf("\n   ❌ Investigation needs more evidence or refinement\n");
        }
    }
    
    // إحصائيات نهائية
    printf("\n\n");
    hunter_stats(&hunter);
    reasoning_stats(&reasoning);
    
    // تنظيف
    tunnel_system_cleanup(&tunnel_system);
    
    printf("\n");
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║              🎊 ADVANCED INVESTIGATION COMPLETE 🎊           ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");
}

int main() {
    srand(time(NULL));
    
    // إنشاء قضية معقدة
    ComplexCase stock_case = create_stock_manipulation_case();
    
    // تشغيل التحقيق المتقدم
    run_advanced_investigation(&stock_case);
    
    return 0;
}
