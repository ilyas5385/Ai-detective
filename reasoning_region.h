#ifndef REASONING_REGION_H
#define REASONING_REGION_H

#include "tunnel_system.h"
#include "hunter_region.h"

#define MAX_HYPOTHESES 32

// 💡 Hypothesis Structure
typedef struct {
    uint32_t id;
    char description[256];
    double prior_probability;      // الاحتمال الأولي (Prior)
    double likelihood;             // احتمالية الأدلة | الفرضية P(E|H)
    double posterior_probability;  // الاحتمال البعدي (Posterior)
    uint32_t supporting_evidence[16];
    uint32_t num_supporting;
    uint32_t contradicting_evidence[16];
    uint32_t num_contradicting;
    bool active;
    uint64_t last_update;
} Hypothesis;

// 🧠 REASONING Region
typedef struct {
    Hypothesis hypotheses[MAX_HYPOTHESES];
    uint32_t num_hypotheses;
    
    Tunnel* input_tunnel;      // من HUNTER
    Tunnel* output_tunnel;     // إلى MEMORY/CONSCIOUSNESS
    
    uint32_t bayesian_updates;
    uint32_t hypotheses_generated;
    uint32_t hypotheses_rejected;
    
    bool active;
} ReasoningRegion;

// 🔧 تهيئة REASONING Region
void reasoning_init(ReasoningRegion* reasoning, TunnelSystem* tunnel_system);

// 💡 توليد فرضية جديدة
Hypothesis* reasoning_generate_hypothesis(ReasoningRegion* reasoning, 
                                          const char* description,
                                          double prior);

// 📊 تحديث Bayesian للفرضية بناءً على دليل جديد
void reasoning_bayesian_update(Hypothesis* hypothesis, 
                               const Evidence* evidence,
                               bool supports);

// 🎯 اختيار أفضل فرضية
Hypothesis* reasoning_select_best_hypothesis(ReasoningRegion* reasoning);

// ⚡ دورة معالجة REASONING
void reasoning_process_cycle(ReasoningRegion* reasoning);

// 📊 إحصائيات REASONING
void reasoning_stats(const ReasoningRegion* reasoning);

// 🔄 إعادة حساب جميع الفرضيات
void reasoning_recalculate_all(ReasoningRegion* reasoning);

#endif // REASONING_REGION_H
