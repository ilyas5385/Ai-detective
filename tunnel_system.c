#include "tunnel_system.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

// 📤 إرسال رسالة عبر Tunnel
bool tunnel_send(Tunnel* tunnel, const TunnelMessage* msg) {
    if (!tunnel || !tunnel->active) {
        return false;
    }
    
    if (tunnel->count >= TUNNEL_QUEUE_SIZE) {
        printf("⚠️  Tunnel %u is FULL! Message dropped.\n", tunnel->id);
        return false;
    }
    
    // نسخ الرسالة إلى الطابور
    memcpy(&tunnel->queue[tunnel->tail], msg, sizeof(TunnelMessage));
    tunnel->tail = (tunnel->tail + 1) % TUNNEL_QUEUE_SIZE;
    tunnel->count++;
    tunnel->bandwidth_usage += sizeof(TunnelMessage);
    
    return true;
}

// 📥 استقبال رسالة من Tunnel
bool tunnel_receive(Tunnel* tunnel, TunnelMessage* msg) {
    if (!tunnel || !tunnel->active || tunnel->count == 0) {
        return false;
    }
    
    // قراءة الرسالة من الطابور
    memcpy(msg, &tunnel->queue[tunnel->head], sizeof(TunnelMessage));
    tunnel->head = (tunnel->head + 1) % TUNNEL_QUEUE_SIZE;
    tunnel->count--;
    
    return true;
}

// 🔧 إنشاء Tunnel جديد
Tunnel* tunnel_create(TunnelSystem* system, uint32_t from, uint32_t to) {
    if (!system || system->num_tunnels >= MAX_TUNNELS) {
        return NULL;
    }
    
    Tunnel* tunnel = &system->tunnels[system->num_tunnels];
    tunnel->id = system->num_tunnels;
    tunnel->from_region = from;
    tunnel->to_region = to;
    tunnel->head = 0;
    tunnel->tail = 0;
    tunnel->count = 0;
    tunnel->active = true;
    tunnel->bandwidth_usage = 0.0;
    
    system->num_tunnels++;
    
    printf("✅ Tunnel %u created: Region %u → Region %u\n", 
           tunnel->id, from, to);
    
    return tunnel;
}

// 📊 إحصائيات Tunnel
void tunnel_stats(const Tunnel* tunnel) {
    if (!tunnel) return;
    
    printf("\n📊 Tunnel %u Statistics:\n", tunnel->id);
    printf("   From: Region %u → To: Region %u\n", 
           tunnel->from_region, tunnel->to_region);
    printf("   Status: %s\n", tunnel->active ? "🟢 Active" : "🔴 Inactive");
    printf("   Messages in queue: %u / %u\n", tunnel->count, TUNNEL_QUEUE_SIZE);
    printf("   Bandwidth usage: %.2f KB\n", tunnel->bandwidth_usage / 1024.0);
}

// 🧹 تنظيف النظام
void tunnel_system_cleanup(TunnelSystem* system) {
    if (!system) return;
    
    for (uint32_t i = 0; i < system->num_tunnels; i++) {
        system->tunnels[i].active = false;
    }
    
    printf("🧹 Tunnel system cleaned up. Total messages: %lu sent, %lu received\n",
           system->total_messages_sent, system->total_messages_received);
}

// 🔄 معالجة جميع الرسائل في النظام (دورة واحدة)
void tunnel_system_process_cycle(TunnelSystem* system) {
    TunnelMessage msg;
    
    for (uint32_t i = 0; i < system->num_tunnels; i++) {
        Tunnel* tunnel = &system->tunnels[i];
        
        while (tunnel_receive(tunnel, &msg)) {
            system->total_messages_received++;
            
            // هنا يمكن توجيه الرسالة للمنطقة المستهدفة
            printf("📨 Message routed: %s → Region %u (weight: %.2f)\n",
                   msg.evidence_id, tunnel->to_region, msg.weight);
        }
    }
}
