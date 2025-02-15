// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vcpu_top.h for the primary calling header

#include "verilated.h"

#include "Vcpu_top___024root.h"

VL_INLINE_OPT void Vcpu_top___024root___ico_sequent__TOP__0(Vcpu_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_top___024root___ico_sequent__TOP__0\n"); );
    // Body
    vlSelf->cpu_top__DOT__wr_en_reg = (IData)((0x13U 
                                               == (0x707fU 
                                                   & vlSelf->inst)));
    vlSelf->cpu_top__DOT__rd_data = ((IData)(vlSelf->cpu_top__DOT__wr_en_reg)
                                      ? (((0x13U == 
                                           (0x7fU & vlSelf->inst))
                                           ? (((- (IData)(
                                                          (vlSelf->inst 
                                                           >> 0x1fU))) 
                                               << 0xcU) 
                                              | (vlSelf->inst 
                                                 >> 0x14U))
                                           : 0U) + 
                                         vlSelf->cpu_top__DOT__u_rf__DOT__gpr
                                         [(0x1fU & 
                                           (vlSelf->inst 
                                            >> 0xfU))])
                                      : 0U);
}

void Vcpu_top___024root___eval_ico(Vcpu_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_top___024root___eval_ico\n"); );
    // Body
    if (vlSelf->__VicoTriggered.at(0U)) {
        Vcpu_top___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Vcpu_top___024root___eval_act(Vcpu_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_top___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vcpu_top___024root___nba_sequent__TOP__0(Vcpu_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_top___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*0:0*/ __Vdlyvset__cpu_top__DOT__u_rf__DOT__gpr__v0;
    __Vdlyvset__cpu_top__DOT__u_rf__DOT__gpr__v0 = 0;
    CData/*4:0*/ __Vdlyvdim0__cpu_top__DOT__u_rf__DOT__gpr__v31;
    __Vdlyvdim0__cpu_top__DOT__u_rf__DOT__gpr__v31 = 0;
    IData/*31:0*/ __Vdlyvval__cpu_top__DOT__u_rf__DOT__gpr__v31;
    __Vdlyvval__cpu_top__DOT__u_rf__DOT__gpr__v31 = 0;
    CData/*0:0*/ __Vdlyvset__cpu_top__DOT__u_rf__DOT__gpr__v31;
    __Vdlyvset__cpu_top__DOT__u_rf__DOT__gpr__v31 = 0;
    // Body
    __Vdlyvset__cpu_top__DOT__u_rf__DOT__gpr__v0 = 0U;
    __Vdlyvset__cpu_top__DOT__u_rf__DOT__gpr__v31 = 0U;
    if (vlSelf->rst) {
        vlSelf->cpu_top__DOT__u_rf__DOT__unnamedblk1__DOT__i = 0x20U;
        vlSelf->pc = 0x80000000U;
        __Vdlyvset__cpu_top__DOT__u_rf__DOT__gpr__v0 = 1U;
    } else {
        vlSelf->pc = ((IData)(4U) + vlSelf->pc);
        if (((IData)(vlSelf->cpu_top__DOT__wr_en_reg) 
             & (0U != (0x1fU & (vlSelf->inst >> 7U))))) {
            __Vdlyvval__cpu_top__DOT__u_rf__DOT__gpr__v31 
                = vlSelf->cpu_top__DOT__rd_data;
            __Vdlyvset__cpu_top__DOT__u_rf__DOT__gpr__v31 = 1U;
            __Vdlyvdim0__cpu_top__DOT__u_rf__DOT__gpr__v31 
                = (0x1fU & (vlSelf->inst >> 7U));
        }
    }
    if (__Vdlyvset__cpu_top__DOT__u_rf__DOT__gpr__v0) {
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[1U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[2U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[3U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[4U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[5U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[6U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[7U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[8U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[9U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0xaU] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0xbU] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0xcU] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0xdU] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0xeU] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0xfU] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0x10U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0x11U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0x12U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0x13U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0x14U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0x15U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0x16U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0x17U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0x18U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0x19U] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0x1aU] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0x1bU] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0x1cU] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0x1dU] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0x1eU] = 0U;
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0x1fU] = 0U;
    }
    if (__Vdlyvset__cpu_top__DOT__u_rf__DOT__gpr__v31) {
        vlSelf->cpu_top__DOT__u_rf__DOT__gpr[__Vdlyvdim0__cpu_top__DOT__u_rf__DOT__gpr__v31] 
            = __Vdlyvval__cpu_top__DOT__u_rf__DOT__gpr__v31;
    }
}

VL_INLINE_OPT void Vcpu_top___024root___nba_sequent__TOP__1(Vcpu_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_top___024root___nba_sequent__TOP__1\n"); );
    // Body
    vlSelf->cpu_top__DOT__rd_data = ((IData)(vlSelf->cpu_top__DOT__wr_en_reg)
                                      ? (((0x13U == 
                                           (0x7fU & vlSelf->inst))
                                           ? (((- (IData)(
                                                          (vlSelf->inst 
                                                           >> 0x1fU))) 
                                               << 0xcU) 
                                              | (vlSelf->inst 
                                                 >> 0x14U))
                                           : 0U) + 
                                         vlSelf->cpu_top__DOT__u_rf__DOT__gpr
                                         [(0x1fU & 
                                           (vlSelf->inst 
                                            >> 0xfU))])
                                      : 0U);
}

void Vcpu_top___024root___eval_nba(Vcpu_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_top___024root___eval_nba\n"); );
    // Body
    if (vlSelf->__VnbaTriggered.at(0U)) {
        Vcpu_top___024root___nba_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
        Vcpu_top___024root___nba_sequent__TOP__1(vlSelf);
    }
}

void Vcpu_top___024root___eval_triggers__ico(Vcpu_top___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vcpu_top___024root___dump_triggers__ico(Vcpu_top___024root* vlSelf);
#endif  // VL_DEBUG
void Vcpu_top___024root___eval_triggers__act(Vcpu_top___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vcpu_top___024root___dump_triggers__act(Vcpu_top___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vcpu_top___024root___dump_triggers__nba(Vcpu_top___024root* vlSelf);
#endif  // VL_DEBUG

void Vcpu_top___024root___eval(Vcpu_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_top___024root___eval\n"); );
    // Init
    CData/*0:0*/ __VicoContinue;
    VlTriggerVec<1> __VpreTriggered;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    vlSelf->__VicoIterCount = 0U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        __VicoContinue = 0U;
        Vcpu_top___024root___eval_triggers__ico(vlSelf);
        if (vlSelf->__VicoTriggered.any()) {
            __VicoContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VicoIterCount))) {
#ifdef VL_DEBUG
                Vcpu_top___024root___dump_triggers__ico(vlSelf);
#endif
                VL_FATAL_MT("/home/wizard/ysyx-workbench/npc/vsrc/top.v", 1, "", "Input combinational region did not converge.");
            }
            vlSelf->__VicoIterCount = ((IData)(1U) 
                                       + vlSelf->__VicoIterCount);
            Vcpu_top___024root___eval_ico(vlSelf);
        }
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        __VnbaContinue = 0U;
        vlSelf->__VnbaTriggered.clear();
        vlSelf->__VactIterCount = 0U;
        vlSelf->__VactContinue = 1U;
        while (vlSelf->__VactContinue) {
            vlSelf->__VactContinue = 0U;
            Vcpu_top___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    Vcpu_top___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("/home/wizard/ysyx-workbench/npc/vsrc/top.v", 1, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                Vcpu_top___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                Vcpu_top___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("/home/wizard/ysyx-workbench/npc/vsrc/top.v", 1, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            Vcpu_top___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void Vcpu_top___024root___eval_debug_assertions(Vcpu_top___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_top___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst & 0xfeU))) {
        Verilated::overWidthError("rst");}
}
#endif  // VL_DEBUG
