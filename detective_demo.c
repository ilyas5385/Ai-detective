#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tunnel_system.h"
#include "hunter_region.h"
#include "reasoning_region.h"

// 🎭 قضية تركيبية: سرقة الماس من متحف
typedef struct {
    const char* name;
    const char* description;
    Evidence evidence[10];
    int num_evidence;
} SyntheticCase;

// 🎨 إنشاء قضية تركيبية
SyntheticCase create_diamond_heist_case() {
    SyntheticCase case_data;
    case_data.name = "The Diamond Museum Heist";
    case_data.description = "A priceless diamond was stolen from the National Museum";
    case_data.num_evidence = 8;
    
    // دليل 1: بصمات
    Evidence e1 = {0};
    strcpy(e1.id, "EVIDENCE_001");
    strcpy(e1.content, "Fingerprints found on display case");
    e1.weight = 0.85;
    strcpy(e1.type, "physical");
    strcpy(e1.source, "Forensics Lab");
    e1.timestamp = time(NULL) - 86400;
    e1.verified = true;
    case_data.evidence[0] = e1;
    
    // دليل 2: كاميرا المراقبة
    Evidence e2 = {0};
    strcpy(e2.id, "EVIDENCE_002");
    strcpy(e2.content, "CCTV footage shows person in black hoodie");
    e2.weight = 0.70;
    strcpy(e2.type, "video");
    strcpy(e2.source, "Security System");
    e2.timestamp = time(NULL) - 82800;
    e2.verified = true;
    case_data.evidence[1] = e2;
    
    // دليل 3: شاهد عيان
    Evidence e3 = {0};
    strcpy(e3.id, "EVIDENCE_003");
    strcpy(e3.content, "Witness reports seeing suspicious van");
    e3.weight = 0.55;
    strcpy(e3.type, "testimonial");
    strcpy(e3.source, "Witness #1");
    e3.timestamp = time(NULL) - 79200;
    e3.verified = false;
    case_data.evidence[2] = e3;
    
    // دليل 4: أدوات السطو
    Evidence e4 = {0};
    strcpy(e4.id, "EVIDENCE_004");
    strcpy(e4.content, "Professional glass-cutting tools found nearby");
    e4.weight = 0.90;
    strcpy(e4.type, "physical");
    strcpy(e4.source, "Crime Scene");
    e4.timestamp = time(NULL) - 75600;
    e4.verified = true;
    case_data.evidence[3] = e4;
    
    // دليل 5: سجلات الدخول
    Evidence e5 = {0};
    strcpy(e5.id, "EVIDENCE_005");
    strcpy(e5.content, "Museum employee accessed room at 2 AM");
    e5.weight = 0.78;
    strcpy(e5.type, "digital");
    strcpy(e5.source, "Access Control System");
    e5.timestamp = time(NULL) - 72000;
    e5.verified = true;
    case_data.evidence[4] = e5;
    
    // دليل 6: سجل جنائي
    Evidence e6 = {0};
    strcpy(e6.id, "EVIDENCE_006");
    strcpy(e6.content, "Suspect has prior art theft convictions");
    e6.weight = 0.65;
    strcpy(e6.type, "background");
    strcpy(e6.source, "Police Database");
    e6.timestamp = time(NULL) - 68400;
    e6.verified = true;
    case_data.evidence[5] = e6;
    
    // دليل 7: مكالمة هاتفية مشبوهة
    Evidence e7 = {0};
    strcpy(e7.id, "EVIDENCE_007");
    strcpy(e7.content, "Intercepted call discussing 'the package'");
    e7.weight = 0.50;
    strcpy(e7.type, "communication");
    strcpy(e7.source, "Phone Tap");
    e7.timestamp = time(NULL) - 64800;
    e7.verified = false;
    case_data.evidence[6] = e7;
    
    // دليل 8: دليل مُضلل (شذوذ)
    Evidence e8 = {0};
    strcpy(e8.id, "EVIDENCE_008");
    strcpy(e8.content, "Anonymous tip pointing to wrong location");
    e8.weight = 0.15;
    strcpy(e8.type, "anomalous");
    strcpy(e8.source, "unknown");
    e8.timestamp = time(NULL) - 61200;
    e8.verified = false;
    case_data.evidence[7] = e8;
    
    return case_data;
}

// 🎯 تشغيل المحقق الاصطناعي
void run_detective_ai(SyntheticCase* case_data) {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║          🕵️  ARTIFICIAL DETECTIVE AI SYSTEM 🕵️            ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("📋 CASE: %s\n", case_data->name);
    printf("📝 Description: %s\n", case_data->description);
    printf("📊 Total Evidence: %d\n", case_data->num_evidence);
    printf("\n");
    
    // تهيئة النظام
    TunnelSystem tunnel_system = {0};
    HunterRegion hunter;
    ReasoningRegion reasoning;
    
    hunter_init(&hunter, &tunnel_system);
    reasoning_init(&reasoning, &tunnel_system);
    
    // توليد فرضيات أولية
    printf("\n💡 GENERATING INITIAL HYPOTHESES\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    reasoning_generate_hypothesis(&reasoning,
        "Hypothesis 1: Inside job by museum employee",
        0.40);
    
    reasoning_generate_hypothesis(&reasoning,
        "Hypothesis 2: Professional art thief gang",
        0.35);
    
    reasoning_generate_hypothesis(&reasoning,
        "Hypothesis 3: Amateur theft with inside help",
        0.20);
    
    reasoning_generate_hypothesis(&reasoning,
        "Hypothesis 4: Elaborate insurance fraud",
        0.05);
    
    // معالجة الأدلة
    printf("\n\n🔍 PROCESSING EVIDENCE THROUGH HUNTER REGION\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    for (int i = 0; i < case_data->num_evidence; i++) {
        Evidence* e = &case_data->evidence[i];
        
        printf("\n[Evidence %d/%d]\n", i + 1, case_data->num_evidence);
        
        // Cell 1: Search Source
        search_source_process(&hunter.search_cell, e);
        
        // Cell 4: Anomaly Detection
        anomaly_detector_process(&hunter.anomaly_cell, e);
        
        // معالجة في REASONING
        reasoning_process_cycle(&reasoning);
        
        // كل 3 أدلة، نكتشف نمط أو كيان
        if ((i + 1) % 3 == 0) {
            hunter_process_cycle(&hunter);
        }
    }
    
    // إعادة حساب الفرضيات
    printf("\n");
    reasoning_recalculate_all(&reasoning);
    
    // اختيار أفضل فرضية
    printf("\n\n🎯 SELECTING BEST HYPOTHESIS\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    Hypothesis* best = reasoning_select_best_hypothesis(&reasoning);
    if (best) {
        printf("\n🏆 MOST PROBABLE HYPOTHESIS:\n");
        printf("   %s\n", best->description);
        printf("   Confidence: %.1f%%\n", best->posterior_probability * 100);
        printf("   Supporting evidence: %u\n", best->num_supporting);
        printf("   Contradicting evidence: %u\n", best->num_contradicting);
    }
    
    // إحصائيات نهائية
    printf("\n\n");
    hunter_stats(&hunter);
    reasoning_stats(&reasoning);
    
    // إحصائيات Tunnels
    printf("\n📊 TUNNEL SYSTEM STATISTICS\n");
    printf("═══════════════════════════════════════\n");
    for (uint32_t i = 0; i < tunnel_system.num_tunnels; i++) {
        tunnel_stats(&tunnel_system.tunnels[i]);
    }
    
    printf("\n✅ Total messages sent: %lu\n", tunnel_system.total_messages_sent);
    printf("✅ Total messages received: %lu\n", tunnel_system.total_messages_received);
    
    // تنظيف
    tunnel_system_cleanup(&tunnel_system);
    
    printf("\n");
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║                 🎊 INVESTIGATION COMPLETE 🎊               ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
}

int main() {
    srand(time(NULL));
    
    // إنشاء قضية تركيبية
    SyntheticCase diamond_case = create_diamond_heist_case();
    
    // تشغيل المحقق الاصطناعي
    run_detective_ai(&diamond_case);
    
    return 0;
}
