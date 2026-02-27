import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from matplotlib.patches import FancyBboxPatch, FancyArrowPatch
import numpy as np

# إعداد الشكل
fig, ax = plt.subplots(1, 1, figsize=(16, 12))
ax.set_xlim(0, 16)
ax.set_ylim(0, 12)
ax.axis('off')

# الألوان
color_consciousness = '#FF6B6B'
color_perception = '#4ECDC4'
color_reasoning = '#45B7D1'
color_hunter = '#FFA07A'
color_memory = '#98D8C8'
color_io = '#C7CEEA'
color_tunnel = '#95A5A6'

# عنوان النظام
ax.text(8, 11.5, '🕵️ ARTIFICIAL DETECTIVE AI SYSTEM', 
        fontsize=20, weight='bold', ha='center',
        bbox=dict(boxstyle='round,pad=0.5', facecolor='yellow', alpha=0.3))

# 1. CONSCIOUSNESS (المنسق الرئيسي)
consciousness_box = FancyBboxPatch((6, 9.5), 4, 1.2,
                                  boxstyle="round,pad=0.1",
                                  facecolor=color_consciousness,
                                  edgecolor='black', linewidth=2)
ax.add_patch(consciousness_box)
ax.text(8, 10.1, 'CONSCIOUSNESS', fontsize=12, weight='bold', ha='center')
ax.text(8, 9.75, '(Coordinator Core)', fontsize=9, ha='center', style='italic')

# 2. PERCEPTION
perception_box = FancyBboxPatch((1, 6.5), 3, 1.5,
                               boxstyle="round,pad=0.1",
                               facecolor=color_perception,
                               edgecolor='black', linewidth=2)
ax.add_patch(perception_box)
ax.text(2.5, 7.5, 'PERCEPTION', fontsize=11, weight='bold', ha='center')
ax.text(2.5, 7.1, 'Evidence Analysis', fontsize=9, ha='center')
ax.text(2.5, 6.8, '• Feature extraction', fontsize=7, ha='center')
ax.text(2.5, 6.6, '• Weight calculation', fontsize=7, ha='center')

# 3. REASONING
reasoning_box = FancyBboxPatch((12, 6.5), 3, 1.5,
                              boxstyle="round,pad=0.1",
                              facecolor=color_reasoning,
                              edgecolor='black', linewidth=2)
ax.add_patch(reasoning_box)
ax.text(13.5, 7.5, 'REASONING', fontsize=11, weight='bold', ha='center')
ax.text(13.5, 7.1, 'Hypothesis Engine', fontsize=9, ha='center')
ax.text(13.5, 6.8, '• Bayesian updates', fontsize=7, ha='center')
ax.text(13.5, 6.6, '• Probability calc', fontsize=7, ha='center')

# 4. HUNTER REGION (مع الخلايا الفرعية)
hunter_main = FancyBboxPatch((5.5, 3), 5, 2.5,
                            boxstyle="round,pad=0.1",
                            facecolor=color_hunter,
                            edgecolor='black', linewidth=3,
                            linestyle='--')
ax.add_patch(hunter_main)
ax.text(8, 5.2, '🦅 HUNTER REGION', fontsize=12, weight='bold', ha='center')

# خلايا HUNTER الفرعية
cell_width = 1.1
cell_height = 0.6
cells = [
    (6, 4.2, 'Cell_Search\nSource', '🔍'),
    (7.3, 4.2, 'Cell_Pattern\nDetection', '🧬'),
    (8.6, 4.2, 'Cell_Entity\nMatching', '🎯'),
    (9.9, 4.2, 'Cell_Anomaly\nDetector', '⚠️')
]

for x, y, name, emoji in cells:
    cell_box = FancyBboxPatch((x, y), cell_width, cell_height,
                             boxstyle="round,pad=0.05",
                             facecolor='#FFEAA7',
                             edgecolor='#2d3436', linewidth=1.5)
    ax.add_patch(cell_box)
    ax.text(x + cell_width/2, y + cell_height/2 + 0.15, emoji, 
            fontsize=10, ha='center')
    ax.text(x + cell_width/2, y + cell_height/2 - 0.15, name, 
            fontsize=6, ha='center', va='center')

# 5. MEMORY
memory_box = FancyBboxPatch((1, 1), 3, 1.2,
                           boxstyle="round,pad=0.1",
                           facecolor=color_memory,
                           edgecolor='black', linewidth=2)
ax.add_patch(memory_box)
ax.text(2.5, 1.8, 'MEMORY', fontsize=11, weight='bold', ha='center')
ax.text(2.5, 1.4, 'Case Archive', fontsize=9, ha='center')
ax.text(2.5, 1.1, '& Experience', fontsize=9, ha='center')

# 6. IO
io_box = FancyBboxPatch((12, 1), 3, 1.2,
                       boxstyle="round,pad=0.1",
                       facecolor=color_io,
                       edgecolor='black', linewidth=2)
ax.add_patch(io_box)
ax.text(13.5, 1.8, 'IO', fontsize=11, weight='bold', ha='center')
ax.text(13.5, 1.4, 'Load / Save', fontsize=9, ha='center')
ax.text(13.5, 1.1, 'Data Interface', fontsize=9, ha='center')

# رسم Tunnels (قنوات الاتصال)
tunnels = [
    # من CONSCIOUSNESS
    (8, 9.5, 2.5, 8, 'Tunnel 1'),
    (8, 9.5, 13.5, 8, 'Tunnel 2'),
    (8, 9.5, 8, 5.5, 'Tunnel 3'),
    
    # من PERCEPTION إلى HUNTER
    (4, 7.2, 6.5, 4.5, 'Tunnel 4'),
    
    # من HUNTER إلى REASONING
    (10.5, 4.5, 12, 7.2, 'Tunnel 5'),
    
    # من HUNTER إلى MEMORY
    (6.5, 3, 4, 2.2, 'Tunnel 6'),
    
    # من REASONING إلى CONSCIOUSNESS
    (13.5, 8, 10, 9.5, 'Tunnel 7'),
    
    # من MEMORY إلى IO
    (4, 1.6, 12, 1.6, 'Tunnel 8'),
]

for x1, y1, x2, y2, label in tunnels:
    arrow = FancyArrowPatch((x1, y1), (x2, y2),
                          arrowstyle='->,head_width=0.4,head_length=0.4',
                          color=color_tunnel, linewidth=2, alpha=0.6,
                          linestyle='--')
    ax.add_patch(arrow)

# إضافة تسميات توضيحية
ax.text(8, 0.3, '📡 Tunnels: Lightweight communication channels between regions', 
        fontsize=9, ha='center', style='italic',
        bbox=dict(boxstyle='round,pad=0.3', facecolor='lightgray', alpha=0.3))

# Legend
legend_elements = [
    mpatches.Patch(color=color_consciousness, label='Coordinator'),
    mpatches.Patch(color=color_perception, label='Input Processing'),
    mpatches.Patch(color=color_reasoning, label='Inference Engine'),
    mpatches.Patch(color=color_hunter, label='Investigation Core'),
    mpatches.Patch(color=color_memory, label='Knowledge Base'),
    mpatches.Patch(color=color_io, label='Data Interface'),
]
ax.legend(handles=legend_elements, loc='upper left', fontsize=8, framealpha=0.9)

plt.tight_layout()
plt.savefig('/home/claude/detective_ai_architecture.png', dpi=300, bbox_inches='tight')
print("✅ Architecture diagram saved!")

# رسم بياني للإحصائيات
fig2, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(14, 10))
fig2.suptitle('🔍 DETECTIVE AI - Evidence Processing Statistics', 
              fontsize=16, weight='bold')

# 1. توزيع أوزان الأدلة
evidence_weights = [0.85, 0.70, 0.55, 0.90, 0.78, 0.65, 0.50, 0.15]
evidence_labels = [f'E{i+1}' for i in range(8)]
colors = ['#2ecc71' if w > 0.7 else '#f39c12' if w > 0.4 else '#e74c3c' 
          for w in evidence_weights]

ax1.bar(evidence_labels, evidence_weights, color=colors, edgecolor='black', linewidth=1.5)
ax1.set_ylabel('Weight', fontsize=11, weight='bold')
ax1.set_title('Evidence Weights Distribution', fontsize=12, weight='bold')
ax1.axhline(y=0.7, color='green', linestyle='--', alpha=0.5, label='High confidence')
ax1.axhline(y=0.4, color='orange', linestyle='--', alpha=0.5, label='Medium confidence')
ax1.legend()
ax1.grid(axis='y', alpha=0.3)

# 2. أنواع الأدلة
evidence_types = ['Physical', 'Video', 'Testimonial', 'Physical', 
                  'Digital', 'Background', 'Communication', 'Anomalous']
type_counts = {}
for t in evidence_types:
    type_counts[t] = type_counts.get(t, 0) + 1

ax2.pie(type_counts.values(), labels=type_counts.keys(), autopct='%1.1f%%',
        colors=['#3498db', '#e74c3c', '#2ecc71', '#f39c12', '#9b59b6'],
        startangle=90)
ax2.set_title('Evidence Types Distribution', fontsize=12, weight='bold')

# 3. تطور احتمالية الفرضيات
hypotheses = ['Inside job', 'Professional gang', 'Amateur theft', 'Insurance fraud']
initial_probs = [0.40, 0.35, 0.20, 0.05]
final_probs = [0.45, 0.30, 0.20, 0.05]  # محاكاة

x_pos = np.arange(len(hypotheses))
width = 0.35

ax3.bar(x_pos - width/2, initial_probs, width, label='Initial', 
        color='skyblue', edgecolor='black')
ax3.bar(x_pos + width/2, final_probs, width, label='After Evidence',
        color='lightcoral', edgecolor='black')
ax3.set_ylabel('Probability', fontsize=11, weight='bold')
ax3.set_title('Hypothesis Probability Evolution', fontsize=12, weight='bold')
ax3.set_xticks(x_pos)
ax3.set_xticklabels(hypotheses, rotation=15, ha='right')
ax3.legend()
ax3.grid(axis='y', alpha=0.3)

# 4. إحصائيات HUNTER Cells
cell_names = ['Search\nSource', 'Pattern\nDetection', 'Entity\nMatching', 'Anomaly\nDetector']
cell_activity = [8, 1, 1, 1]  # عدد العمليات

bars = ax4.barh(cell_names, cell_activity, color=color_hunter, edgecolor='black', linewidth=1.5)
ax4.set_xlabel('Number of Operations', fontsize=11, weight='bold')
ax4.set_title('HUNTER Cell Activity', fontsize=12, weight='bold')
ax4.grid(axis='x', alpha=0.3)

# إضافة القيم على الأعمدة
for i, (bar, val) in enumerate(zip(bars, cell_activity)):
    ax4.text(val + 0.2, i, str(val), va='center', fontsize=10, weight='bold')

plt.tight_layout()
plt.savefig('/home/claude/detective_ai_statistics.png', dpi=300, bbox_inches='tight')
print("✅ Statistics diagram saved!")

print("\n🎉 All visualizations created successfully!")
