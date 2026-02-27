#include "reasoning_region.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// 🔧 تهيئة REASONING Region
void reasoning_init(ReasoningRegion* reasoning, TunnelSystem* tunnel_system) {
    memset(reasoning, 0, sizeof(ReasoningRegion));
    reasoning->active = true;
    
    // إنشاء Tunnels
    reasoning->input_tunnel = tunnel_create(tunnel_system,
                                           REGION_HUNTER,
                                           REGION_REASONING);
    reasoning->output_tunnel = tunnel_create(tunnel_system,
                                            REGION_REASONING,
                                            REGION_CONSCIOUSNESS);
    
    printf("🧠 REASONING Region initialized\n");
}

// 💡 توليد فرضية جديدة
Hypothesis* reasoning_generate_hypothesis(ReasoningRegion* reasoning,
                                         const char* description,
                                         double prior) {
    if (!reasoning || reasoning->num_hypotheses >= MAX_HYPOTHESES) {
        return NULL;
    }
    
    Hypothesis* h = &reasoning->hypotheses[reasoning->num_hypotheses];
    h->id = reasoning->num_hypotheses;
    strncpy(h->description, description, 255);
    h->prior_probability = prior;
    h->likelihood = 0.5; // محايد في البداية
    h->posterior_probability = prior;
    h->num_supporting = 0;
    h->num_contradicting = 0;
    h->active = true;
    h->last_update = time(NULL);
    
    reasoning->num_hypotheses++;
    reasoning->hypotheses_generated++;
    
    printf("💡 [REASONING] Generated hypothesis %u: %s (prior: %.3f)\n",
           h->id, h->description, prior);
    
    return h;
}

// 📊 تحديث Bayesian للفرضية بناءً على دليل جديد
void reasoning_bayesian_update(Hypothesis* hypothesis,
                               const Evidence* evidence,
                               bool supports) {
    if (!hypothesis || !evidence) return;
    
    // قاعدة بايز: P(H|E) = P(E|H) * P(H) / P(E)
    // نبسّط: P(H|E) ∝ P(E|H) * P(H)
    
    double evidence_weight = evidence->weight;
    
    if (supports) {
        // الدليل يدعم الفرضية
        hypothesis->likelihood = fmin(1.0, hypothesis->likelihood + evidence_weight * 0.3);
        hypothesis->supporting_evidence[hypothesis->num_supporting++] = 
            atoi(evidence->id + 8); // استخراج رقم من معرف الدليل
        
        printf("   ✅ Evidence %s SUPPORTS hypothesis %u (new likelihood: %.3f)\n",
               evidence->id, hypothesis->id, hypothesis->likelihood);
    } else {
        // الدليل يناقض الفرضية
        hypothesis->likelihood = fmax(0.0, hypothesis->likelihood - evidence_weight * 0.4);
        hypothesis->contradicting_evidence[hypothesis->num_contradicting++] = 
            atoi(evidence->id + 8);
        
        printf("   ❌ Evidence %s CONTRADICTS hypothesis %u (new likelihood: %.3f)\n",
               evidence->id, hypothesis->id, hypothesis->likelihood);
    }
    
    // تحديث الاحتمال البعدي
    // Posterior = Likelihood × Prior / Normalization
    hypothesis->posterior_probability = 
        hypothesis->likelihood * hypothesis->prior_probability;
    
    // تطبيع بسيط (في نظام حقيقي نحتاج مجموع جميع الفرضيات)
    hypothesis->posterior_probability = 
        fmin(1.0, hypothesis->posterior_probability / 0.5);
    
    hypothesis->last_update = time(NULL);
    
    printf("   📊 Posterior probability: %.3f\n", hypothesis->posterior_probability);
}

// 🎯 اختيار أفضل فرضية
Hypothesis* reasoning_select_best_hypothesis(ReasoningRegion* reasoning) {
    if (!reasoning || reasoning->num_hypotheses == 0) {
        return NULL;
    }
    
    Hypothesis* best = NULL;
    double max_posterior = -1.0;
    
    for (uint32_t i = 0; i < reasoning->num_hypotheses; i++) {
        Hypothesis* h = &reasoning->hypotheses[i];
        if (h->active && h->posterior_probability > max_posterior) {
            max_posterior = h->posterior_probability;
            best = h;
        }
    }
    
    return best;
}

// ⚡ دورة معالجة REASONING
void reasoning_process_cycle(ReasoningRegion* reasoning) {
    if (!reasoning || !reasoning->active) return;
    
    // استقبال رسائل من HUNTER
    TunnelMessage msg;
    while (tunnel_receive(reasoning->input_tunnel, &msg)) {
        printf("🧠 [REASONING] Processing message: %s (weight: %.2f)\n",
               msg.evidence_id, msg.weight);
        
        // تحديث الفرضيات الموجودة
        for (uint32_t i = 0; i < reasoning->num_hypotheses; i++) {
            Hypothesis* h = &reasoning->hypotheses[i];
            if (!h->active) continue;
            
            // محاكاة تحديث بسيط
            Evidence temp_evidence = {0};
            strncpy(temp_evidence.id, msg.evidence_id, MAX_EVIDENCE_ID - 1);
            temp_evidence.weight = msg.weight;
            
            // قرار عشوائي: هل الدليل يدعم هذه الفرضية؟
            bool supports = (rand() % 100) < (int)(msg.weight * 100);
            
            reasoning_bayesian_update(h, &temp_evidence, supports);
            reasoning->bayesian_updates++;
        }
        
        // إرسال النتائج عبر Tunnel
        TunnelMessage out_msg = msg;
        out_msg.sender_id = REGION_REASONING;
        out_msg.receiver_id = REGION_CONSCIOUSNESS;
        tunnel_send(reasoning->output_tunnel, &out_msg);
    }
}

// 📊 إحصائيات REASONING
void reasoning_stats(const ReasoningRegion* reasoning) {
    if (!reasoning) return;
    
    printf("\n📊 REASONING REGION STATISTICS\n");
    printf("═══════════════════════════════════════\n");
    printf("💡 Active hypotheses: %u / %u\n", 
           reasoning->num_hypotheses, MAX_HYPOTHESES);
    printf("📈 Bayesian updates: %u\n", reasoning->bayesian_updates);
    printf("✨ Hypotheses generated: %u\n", reasoning->hypotheses_generated);
    printf("❌ Hypotheses rejected: %u\n", reasoning->hypotheses_rejected);
    
    printf("\n🎯 HYPOTHESIS RANKING:\n");
    printf("─────────────────────────────────────\n");
    
    // ترتيب الفرضيات حسب الاحتمال البعدي
    for (uint32_t i = 0; i < reasoning->num_hypotheses; i++) {
        const Hypothesis* h = &reasoning->hypotheses[i];
        if (!h->active) continue;
        
        printf("%u. %s\n", i + 1, h->description);
        printf("   Prior: %.3f | Likelihood: %.3f | Posterior: %.3f\n",
               h->prior_probability, h->likelihood, h->posterior_probability);
        printf("   Supporting: %u | Contradicting: %u\n",
               h->num_supporting, h->num_contradicting);
        
        // مؤشر مرئي
        int bar_length = (int)(h->posterior_probability * 40);
        printf("   [");
        for (int j = 0; j < 40; j++) {
            printf("%c", j < bar_length ? '█' : '░');
        }
        printf("] %.1f%%\n\n", h->posterior_probability * 100);
    }
    
    printf("═══════════════════════════════════════\n");
}

// 🔄 إعادة حساب جميع الفرضيات
void reasoning_recalculate_all(ReasoningRegion* reasoning) {
    if (!reasoning) return;
    
    printf("\n🔄 Recalculating all hypotheses...\n");
    
    for (uint32_t i = 0; i < reasoning->num_hypotheses; i++) {
        Hypothesis* h = &reasoning->hypotheses[i];
        if (!h->active) continue;
        
        // إعادة حساب Posterior
        h->posterior_probability = h->likelihood * h->prior_probability;
        h->posterior_probability = fmin(1.0, h->posterior_probability / 0.5);
        
        // رفض الفرضيات الضعيفة جداً
        if (h->posterior_probability < 0.1 && h->num_contradicting > 3) {
            h->active = false;
            reasoning->hypotheses_rejected++;
            printf("   ❌ Hypothesis %u rejected (posterior: %.3f)\n",
                   h->id, h->posterior_probability);
        }
    }
    
    printf("✅ Recalculation complete\n");
}
