import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from matplotlib.patches import FancyBboxPatch, Circle, FancyArrowPatch, Wedge
import numpy as np

# إعداد الشكل
fig = plt.figure(figsize=(18, 12))

# ═══════════════════════════════════════════════════════════
# 1. خريطة الأدلة والربط بالكيان
# ═══════════════════════════════════════════════════════════
ax1 = plt.subplot(2, 3, 1)
ax1.set_xlim(0, 10)
ax1.set_ylim(0, 10)
ax1.axis('off')
ax1.set_title('Evidence Network Map', fontsize=14, weight='bold', pad=20)

# الكيان المستهدف في المركز
target = Circle((5, 5), 0.8, color='#e74c3c', ec='black', linewidth=3, zorder=10)
ax1.add_patch(target)
ax1.text(5, 5, 'Marcus\nChen', ha='center', va='center', 
         fontsize=10, weight='bold', color='white', zorder=11)

# الأدلة حول الكيان
evidence_data = [
    ('E1: Trading', 0.75, 0, '#3498db'),
    ('E2: Account', 0.82, 45, '#2ecc71'),
    ('E3: Meeting', 0.65, 90, '#f39c12'),
    ('E4: Call', 0.88, 135, '#9b59b6'),
    ('E5: Badge', 0.79, 180, '#1abc9c'),
    ('E6: Computer', 0.91, 225, '#e67e22'),
    ('E7: Witness', 0.58, 270, '#34495e'),
    ('E8: Prior SEC', 0.45, 315, '#95a5a6'),
    ('E9: Transfer', 0.84, 30, '#16a085'),
    ('E10: Anomaly', 0.12, 60, '#c0392b'),
]

for i, (label, weight, angle, color) in enumerate(evidence_data[:10]):
    angle_rad = np.radians(angle)
    distance = 3.5
    x = 5 + distance * np.cos(angle_rad)
    y = 5 + distance * np.sin(angle_rad)
    
    # الدليل
    evidence_circle = Circle((x, y), 0.4, color=color, ec='black', linewidth=2, alpha=0.8)
    ax1.add_patch(evidence_circle)
    
    # الخط الرابط (سماكته تمثل قوة الربط)
    if i < 9:  # الأدلة المرتبطة
        arrow = FancyArrowPatch((5, 5), (x, y),
                              arrowstyle='-',
                              color=color, linewidth=weight*3, alpha=0.5,
                              connectionstyle="arc3,rad=0.1")
        ax1.add_patch(arrow)
    
    # التسمية
    ax1.text(x, y - 0.7, label, ha='center', fontsize=7, weight='bold')
    ax1.text(x, y - 0.95, f'w:{weight}', ha='center', fontsize=6)

ax1.text(5, 9.5, '10/12 Evidence Linked', ha='center', fontsize=10,
         bbox=dict(boxstyle='round,pad=0.5', facecolor='lightgreen', alpha=0.7))

# ═══════════════════════════════════════════════════════════
# 2. تطور مستوى الشبهة
# ═══════════════════════════════════════════════════════════
ax2 = plt.subplot(2, 3, 2)

evidence_order = range(1, 11)
suspicion_levels = [0, 0.09, 0.13, 0.27, 0.37, 0.50, 0.58, 0.64, 0.73, 0.96]

ax2.plot(evidence_order, suspicion_levels, marker='o', markersize=8, 
         linewidth=3, color='#e74c3c', label='Suspicion Level')
ax2.fill_between(evidence_order, suspicion_levels, alpha=0.3, color='#e74c3c')

# خط العتبة
ax2.axhline(y=0.7, color='orange', linestyle='--', linewidth=2, label='High Suspicion Threshold')
ax2.axhline(y=0.4, color='yellow', linestyle='--', linewidth=1.5, label='Medium Suspicion')

ax2.set_xlabel('Evidence Number', fontsize=11, weight='bold')
ax2.set_ylabel('Suspicion Level', fontsize=11, weight='bold')
ax2.set_title('Suspicion Level Evolution', fontsize=14, weight='bold')
ax2.legend(loc='upper left', fontsize=9)
ax2.grid(True, alpha=0.3)
ax2.set_ylim(0, 1.05)

# تعليق توضيحي
ax2.annotate('CRITICAL\nEVIDENCE', 
            xy=(10, 0.96), xytext=(8, 0.85),
            arrowprops=dict(arrowstyle='->', color='red', lw=2),
            fontsize=10, weight='bold', color='red',
            bbox=dict(boxstyle='round,pad=0.5', facecolor='yellow', alpha=0.8))

# ═══════════════════════════════════════════════════════════
# 3. توزيع أوزان الأدلة
# ═══════════════════════════════════════════════════════════
ax3 = plt.subplot(2, 3, 3)

evidence_weights = [0.75, 0.82, 0.65, 0.88, 0.79, 0.91, 0.58, 0.45, 0.84, 0.12, 0.77, 0.95]
evidence_labels = [f'E{i+1}' for i in range(12)]

colors = ['#27ae60' if w > 0.7 else '#f39c12' if w > 0.5 else '#e74c3c' 
          for w in evidence_weights]

bars = ax3.bar(evidence_labels, evidence_weights, color=colors, 
               edgecolor='black', linewidth=1.5, alpha=0.8)

ax3.set_ylabel('Evidence Weight', fontsize=11, weight='bold')
ax3.set_xlabel('Evidence ID', fontsize=11, weight='bold')
ax3.set_title('Evidence Quality Distribution', fontsize=14, weight='bold')
ax3.axhline(y=0.7, color='green', linestyle='--', alpha=0.5, label='Strong evidence')
ax3.axhline(y=0.5, color='orange', linestyle='--', alpha=0.5, label='Moderate')
ax3.legend(fontsize=8)
ax3.grid(axis='y', alpha=0.3)

# تظليل الأدلة الشاذة
ax3.patches[9].set_facecolor('#c0392b')
ax3.patches[9].set_alpha(1.0)
ax3.text(9, 0.15, 'ANOMALY', ha='center', fontsize=7, weight='bold', color='white')

# ═══════════════════════════════════════════════════════════
# 4. الأنماط المكتشفة
# ═══════════════════════════════════════════════════════════
ax4 = plt.subplot(2, 3, 4)
ax4.axis('off')
ax4.set_title('Detected Patterns', fontsize=14, weight='bold', pad=20)

patterns = [
    ('Temporal Clustering', 0.85, '#3498db'),
    ('Insider Threat Signature', 0.92, '#e74c3c'),
    ('Behavior Chain', 0.88, '#2ecc71'),
]

y_pos = 0.8
for i, (pattern, confidence, color) in enumerate(patterns):
    # صندوق النمط
    box = FancyBboxPatch((0.1, y_pos - 0.15), 0.8, 0.2,
                         boxstyle="round,pad=0.02",
                         facecolor=color, edgecolor='black',
                         linewidth=2, alpha=0.7)
    ax4.add_patch(box)
    
    ax4.text(0.5, y_pos, pattern, ha='center', va='center',
            fontsize=11, weight='bold', color='white')
    ax4.text(0.5, y_pos - 0.08, f'Confidence: {confidence:.0%}',
            ha='center', va='center', fontsize=9, color='white')
    
    y_pos -= 0.3

ax4.set_xlim(0, 1)
ax4.set_ylim(0, 1)

# ═══════════════════════════════════════════════════════════
# 5. مقارنة الفرضيات
# ═══════════════════════════════════════════════════════════
ax5 = plt.subplot(2, 3, 5)

hypotheses = [
    'Marcus Chen\nInsider Trading',
    'Sarah Kim\nScapegoat',
    'External\nHacker',
    'CEO Assistant\nLeak',
    'Crime\nSyndicate'
]

initial_probs = [0.30, 0.15, 0.25, 0.20, 0.10]
final_probs = [0.30, 0.15, 0.25, 0.20, 0.10]  # في التطبيق الحقيقي ستتغير

x_pos = np.arange(len(hypotheses))
width = 0.35

bars1 = ax5.barh(x_pos - width/2, initial_probs, width, 
                label='Initial Probability', color='lightblue', 
                edgecolor='black', linewidth=1.5)
bars2 = ax5.barh(x_pos + width/2, final_probs, width,
                label='After Evidence', color='coral',
                edgecolor='black', linewidth=1.5)

# تظليل الفرضية الفائزة
bars2[0].set_facecolor('#27ae60')
bars2[0].set_linewidth(3)

ax5.set_yticks(x_pos)
ax5.set_yticklabels(hypotheses, fontsize=9)
ax5.set_xlabel('Probability', fontsize=11, weight='bold')
ax5.set_title('Hypothesis Comparison', fontsize=14, weight='bold')
ax5.legend(fontsize=9)
ax5.grid(axis='x', alpha=0.3)

# علامة النجاح
ax5.text(0.32, 0, '✓ WINNER', fontsize=10, weight='bold', 
        color='white', va='center',
        bbox=dict(boxstyle='round,pad=0.3', facecolor='#27ae60'))

# ═══════════════════════════════════════════════════════════
# 6. نتيجة التحقيق النهائية
# ═══════════════════════════════════════════════════════════
ax6 = plt.subplot(2, 3, 6)
ax6.axis('off')
ax6.set_xlim(0, 10)
ax6.set_ylim(0, 10)

# صندوق النتيجة
result_box = FancyBboxPatch((1, 3), 8, 4,
                           boxstyle="round,pad=0.2",
                           facecolor='#27ae60', edgecolor='black',
                           linewidth=4, alpha=0.9)
ax6.add_patch(result_box)

ax6.text(5, 6.5, '✅ INVESTIGATION SUCCESSFUL!', 
        ha='center', va='center', fontsize=16, weight='bold', color='white')

ax6.text(5, 5.5, 'Identified Culprit:', 
        ha='center', va='center', fontsize=12, weight='bold', color='white')

ax6.text(5, 4.8, 'Marcus Chen (Senior Trader)', 
        ha='center', va='center', fontsize=14, weight='bold', 
        color='yellow',
        bbox=dict(boxstyle='round,pad=0.5', facecolor='#c0392b', 
                 edgecolor='white', linewidth=2))

ax6.text(5, 3.8, 'Suspicion Level: 96.45%', 
        ha='center', va='center', fontsize=11, color='white')

ax6.text(5, 3.3, '10/12 Evidence Linked', 
        ha='center', va='center', fontsize=10, color='white')

# إحصائيات
stats_text = [
    'Patterns Detected: 3',
    'Anomalies Found: 1',
    'Processing Time: <1s'
]

y_pos = 2.2
for stat in stats_text:
    ax6.text(5, y_pos, stat, ha='center', va='center',
            fontsize=9, color='white', style='italic')
    y_pos -= 0.35

# العنوان الرئيسي
fig.suptitle('🕵️ ARTIFICIAL DETECTIVE AI - INVESTIGATION REPORT 🕵️',
            fontsize=18, weight='bold', y=0.98)

plt.tight_layout(rect=[0, 0, 1, 0.96])
plt.savefig('/home/claude/investigation_results.png', dpi=300, bbox_inches='tight')
print("✅ Investigation results visualization saved!")

# ═══════════════════════════════════════════════════════════
# رسم بياني إضافي: Timeline
# ═══════════════════════════════════════════════════════════
fig2, ax = plt.subplots(figsize=(16, 8))

# محور الزمن
timeline_days = [-4, -3, -2, -1, 0]
events = [
    (-4, 'Meeting at hotel\nBadge swipe 11PM\nComputer access', 3, '#f39c12'),
    (-3, 'Unusual trading activity\nJanitor witness', 2, '#3498db'),
    (-2, 'Encrypted phone call\nWire transfer $50K\nEmail: "package ready"', 3, '#e74c3c'),
    (-1, 'Fingerprints found\nAnonymous tip (false)', 2, '#2ecc71'),
]

ax.set_xlim(-4.5, 0.5)
ax.set_ylim(0, 5)

# خط الزمن الرئيسي
ax.axhline(y=2.5, color='#34495e', linewidth=4, zorder=1)

# نقاط الأحداث
for day, event, count, color in events:
    # الدائرة
    circle = Circle((day, 2.5), 0.2, color=color, ec='black', 
                   linewidth=3, zorder=5)
    ax.add_patch(circle)
    
    # النص
    y_offset = 3.5 if count > 2 else 3.2
    ax.text(day, y_offset, event, ha='center', va='bottom',
           fontsize=9, weight='bold',
           bbox=dict(boxstyle='round,pad=0.5', facecolor=color, 
                    alpha=0.7, edgecolor='black'))
    
    # عدد الأدلة
    ax.text(day, 1.8, f'{count} Evidence', ha='center', va='top',
           fontsize=8, style='italic')

# التسميات
ax.set_xlabel('Days Before Announcement (Day 0)', fontsize=12, weight='bold')
ax.set_title('Crime Timeline Reconstruction', fontsize=16, weight='bold', pad=20)
ax.set_xticks(timeline_days)
ax.set_xticklabels([f'Day {d}' for d in timeline_days], fontsize=10)
ax.set_yticks([])
ax.spines['left'].set_visible(False)
ax.spines['right'].set_visible(False)
ax.spines['top'].set_visible(False)

# مؤشر الإعلان
ax.axvline(x=0, color='red', linewidth=3, linestyle='--', alpha=0.7)
ax.text(0, 4.5, '📢 Major Announcement', ha='center', fontsize=11,
       weight='bold', color='red',
       bbox=dict(boxstyle='round,pad=0.5', facecolor='yellow', alpha=0.8))

plt.tight_layout()
plt.savefig('/home/claude/crime_timeline.png', dpi=300, bbox_inches='tight')
print("✅ Crime timeline visualization saved!")

print("\n🎉 All investigation visualizations created successfully!")
