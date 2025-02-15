// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_fst_c.h"
#include "Vcpu_top__Syms.h"


void Vcpu_top___024root__trace_chg_sub_0(Vcpu_top___024root* vlSelf, VerilatedFst::Buffer* bufp);

void Vcpu_top___024root__trace_chg_top_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_top___024root__trace_chg_top_0\n"); );
    // Init
    Vcpu_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcpu_top___024root*>(voidSelf);
    Vcpu_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vcpu_top___024root__trace_chg_sub_0((&vlSymsp->TOP), bufp);
}

void Vcpu_top___024root__trace_chg_sub_0(Vcpu_top___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_top___024root__trace_chg_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgIData(oldp+0,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0]),32);
        bufp->chgIData(oldp+1,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[1]),32);
        bufp->chgIData(oldp+2,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[2]),32);
        bufp->chgIData(oldp+3,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[3]),32);
        bufp->chgIData(oldp+4,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[4]),32);
        bufp->chgIData(oldp+5,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[5]),32);
        bufp->chgIData(oldp+6,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[6]),32);
        bufp->chgIData(oldp+7,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[7]),32);
        bufp->chgIData(oldp+8,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[8]),32);
        bufp->chgIData(oldp+9,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[9]),32);
        bufp->chgIData(oldp+10,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[10]),32);
        bufp->chgIData(oldp+11,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[11]),32);
        bufp->chgIData(oldp+12,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[12]),32);
        bufp->chgIData(oldp+13,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[13]),32);
        bufp->chgIData(oldp+14,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[14]),32);
        bufp->chgIData(oldp+15,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[15]),32);
        bufp->chgIData(oldp+16,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[16]),32);
        bufp->chgIData(oldp+17,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[17]),32);
        bufp->chgIData(oldp+18,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[18]),32);
        bufp->chgIData(oldp+19,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[19]),32);
        bufp->chgIData(oldp+20,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[20]),32);
        bufp->chgIData(oldp+21,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[21]),32);
        bufp->chgIData(oldp+22,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[22]),32);
        bufp->chgIData(oldp+23,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[23]),32);
        bufp->chgIData(oldp+24,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[24]),32);
        bufp->chgIData(oldp+25,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[25]),32);
        bufp->chgIData(oldp+26,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[26]),32);
        bufp->chgIData(oldp+27,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[27]),32);
        bufp->chgIData(oldp+28,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[28]),32);
        bufp->chgIData(oldp+29,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[29]),32);
        bufp->chgIData(oldp+30,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[30]),32);
        bufp->chgIData(oldp+31,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[31]),32);
        bufp->chgIData(oldp+32,(vlSelf->cpu_top__DOT__u_rf__DOT__unnamedblk1__DOT__i),32);
    }
    bufp->chgBit(oldp+33,(vlSelf->clk));
    bufp->chgBit(oldp+34,(vlSelf->rst));
    bufp->chgIData(oldp+35,(vlSelf->inst),32);
    bufp->chgIData(oldp+36,(vlSelf->pc),32);
    bufp->chgIData(oldp+37,(((0x13U == (0x7fU & vlSelf->inst))
                              ? (((- (IData)((vlSelf->inst 
                                              >> 0x1fU))) 
                                  << 0xcU) | (vlSelf->inst 
                                              >> 0x14U))
                              : 0U)),32);
    bufp->chgIData(oldp+38,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr
                            [(0x1fU & (vlSelf->inst 
                                       >> 0xfU))]),32);
    bufp->chgIData(oldp+39,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr
                            [(0x1fU & (vlSelf->inst 
                                       >> 0x14U))]),32);
    bufp->chgIData(oldp+40,(((IData)(vlSelf->cpu_top__DOT__wr_en_reg)
                              ? (((0x13U == (0x7fU 
                                             & vlSelf->inst))
                                   ? (((- (IData)((vlSelf->inst 
                                                   >> 0x1fU))) 
                                       << 0xcU) | (vlSelf->inst 
                                                   >> 0x14U))
                                   : 0U) + vlSelf->cpu_top__DOT__u_rf__DOT__gpr
                                 [(0x1fU & (vlSelf->inst 
                                            >> 0xfU))])
                              : 0U)),32);
    bufp->chgCData(oldp+41,((0x1fU & (vlSelf->inst 
                                      >> 0xfU))),5);
    bufp->chgCData(oldp+42,((0x1fU & (vlSelf->inst 
                                      >> 0x14U))),5);
    bufp->chgCData(oldp+43,((0x1fU & (vlSelf->inst 
                                      >> 7U))),5);
    bufp->chgBit(oldp+44,((0x13U == (0x7fU & vlSelf->inst))));
    bufp->chgCData(oldp+45,((7U & (vlSelf->inst >> 0xcU))),3);
    bufp->chgCData(oldp+46,((vlSelf->inst >> 0x19U)),7);
    bufp->chgCData(oldp+47,((0x7fU & vlSelf->inst)),7);
    bufp->chgBit(oldp+48,(vlSelf->cpu_top__DOT__wr_en_reg));
}

void Vcpu_top___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_top___024root__trace_cleanup\n"); );
    // Init
    Vcpu_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcpu_top___024root*>(voidSelf);
    Vcpu_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
