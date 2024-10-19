// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

VL_INLINE_OPT void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
    // Body
    vlSelf->led = ((0xffc0U & (IData)(vlSelf->led)) 
                   | (((IData)(vlSelf->top__DOT__overflow) 
                       << 5U) | (((IData)(vlSelf->ps2_data) 
                                  << 4U) | ((8U & (IData)(vlSelf->data_in)) 
                                            | (((IData)(vlSelf->top__DOT__nextdata_n) 
                                                << 2U) 
                                               | (((IData)(vlSelf->top__DOT__ready) 
                                                   << 1U) 
                                                  | (IData)(vlSelf->top__DOT__key_valid)))))));
}

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    // Body
    if (vlSelf->__VicoTriggered.at(0U)) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    // Init
    CData/*2:0*/ __Vdly__top__DOT__u_ps2_keyboard__DOT__ps2_clk_sync;
    __Vdly__top__DOT__u_ps2_keyboard__DOT__ps2_clk_sync = 0;
    CData/*2:0*/ __Vdly__top__DOT__u_ps2_keyboard__DOT__w_ptr;
    __Vdly__top__DOT__u_ps2_keyboard__DOT__w_ptr = 0;
    CData/*3:0*/ __Vdly__top__DOT__u_ps2_keyboard__DOT__count;
    __Vdly__top__DOT__u_ps2_keyboard__DOT__count = 0;
    // Body
    __Vdly__top__DOT__u_ps2_keyboard__DOT__ps2_clk_sync 
        = vlSelf->top__DOT__u_ps2_keyboard__DOT__ps2_clk_sync;
    __Vdly__top__DOT__u_ps2_keyboard__DOT__count = vlSelf->top__DOT__u_ps2_keyboard__DOT__count;
    __Vdly__top__DOT__u_ps2_keyboard__DOT__w_ptr = vlSelf->top__DOT__u_ps2_keyboard__DOT__w_ptr;
    vlSelf->__Vdly__top__DOT__u_ps2_keyboard__DOT__r_ptr 
        = vlSelf->top__DOT__u_ps2_keyboard__DOT__r_ptr;
    vlSelf->__Vdlyvset__top__DOT__u_ps2_keyboard__DOT__fifo__v0 = 0U;
    vlSelf->__Vdly__top__DOT__ready = vlSelf->top__DOT__ready;
    __Vdly__top__DOT__u_ps2_keyboard__DOT__ps2_clk_sync 
        = ((6U & ((IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT__ps2_clk_sync) 
                  << 1U)) | (IData)(vlSelf->ps2_clk));
    if (vlSelf->rst_n) {
        if (vlSelf->top__DOT__ready) {
            if ((1U & (~ (IData)(vlSelf->top__DOT__nextdata_n)))) {
                vlSelf->__Vdly__top__DOT__u_ps2_keyboard__DOT__r_ptr 
                    = (7U & ((IData)(1U) + (IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT__r_ptr)));
                if (((IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT__w_ptr) 
                     == (7U & ((IData)(1U) + (IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT__r_ptr))))) {
                    vlSelf->__Vdly__top__DOT__ready = 0U;
                }
            }
        }
        if ((IData)((4U == (6U & (IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT__ps2_clk_sync))))) {
            if ((0xaU == (IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT__count))) {
                if ((((~ (IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT__buffer)) 
                      & (IData)(vlSelf->ps2_data)) 
                     & VL_REDXOR_32((0x1ffU & ((IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT__buffer) 
                                               >> 1U))))) {
                    vlSelf->__Vdlyvval__top__DOT__u_ps2_keyboard__DOT__fifo__v0 
                        = (0xffU & ((IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT__buffer) 
                                    >> 1U));
                    vlSelf->__Vdlyvset__top__DOT__u_ps2_keyboard__DOT__fifo__v0 = 1U;
                    vlSelf->__Vdlyvdim0__top__DOT__u_ps2_keyboard__DOT__fifo__v0 
                        = vlSelf->top__DOT__u_ps2_keyboard__DOT__w_ptr;
                    vlSelf->__Vdly__top__DOT__ready = 1U;
                    __Vdly__top__DOT__u_ps2_keyboard__DOT__w_ptr 
                        = (7U & ((IData)(1U) + (IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT__w_ptr)));
                    vlSelf->top__DOT__overflow = ((IData)(vlSelf->top__DOT__overflow) 
                                                  | ((IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT__r_ptr) 
                                                     == 
                                                     (7U 
                                                      & ((IData)(1U) 
                                                         + (IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT__w_ptr)))));
                }
                __Vdly__top__DOT__u_ps2_keyboard__DOT__count = 0U;
            } else {
                vlSelf->top__DOT__u_ps2_keyboard__DOT____Vlvbound_h1a91ade8__0 
                    = vlSelf->ps2_data;
                if ((9U >= (IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT__count))) {
                    vlSelf->top__DOT__u_ps2_keyboard__DOT__buffer 
                        = (((~ ((IData)(1U) << (IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT__count))) 
                            & (IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT__buffer)) 
                           | (0x3ffU & ((IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT____Vlvbound_h1a91ade8__0) 
                                        << (IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT__count))));
                }
                __Vdly__top__DOT__u_ps2_keyboard__DOT__count 
                    = (0xfU & ((IData)(1U) + (IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT__count)));
            }
        }
    } else {
        __Vdly__top__DOT__u_ps2_keyboard__DOT__count = 0U;
        __Vdly__top__DOT__u_ps2_keyboard__DOT__w_ptr = 0U;
        vlSelf->__Vdly__top__DOT__u_ps2_keyboard__DOT__r_ptr = 0U;
        vlSelf->top__DOT__overflow = 0U;
        vlSelf->__Vdly__top__DOT__ready = 0U;
    }
    vlSelf->top__DOT__u_ps2_keyboard__DOT__ps2_clk_sync 
        = __Vdly__top__DOT__u_ps2_keyboard__DOT__ps2_clk_sync;
    vlSelf->top__DOT__u_ps2_keyboard__DOT__w_ptr = __Vdly__top__DOT__u_ps2_keyboard__DOT__w_ptr;
    vlSelf->top__DOT__u_ps2_keyboard__DOT__count = __Vdly__top__DOT__u_ps2_keyboard__DOT__count;
}

extern const VlUnpacked<CData/*6:0*/, 16> Vtop__ConstPool__TABLE_h25bdbd99_0;
extern const VlUnpacked<CData/*6:0*/, 32> Vtop__ConstPool__TABLE_h99acd3d6_0;
extern const VlUnpacked<CData/*7:0*/, 256> Vtop__ConstPool__TABLE_h3b12cc5c_0;

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__1(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__1\n"); );
    // Init
    CData/*7:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*3:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    CData/*3:0*/ __Vtableidx3;
    __Vtableidx3 = 0;
    CData/*4:0*/ __Vtableidx4;
    __Vtableidx4 = 0;
    CData/*4:0*/ __Vtableidx5;
    __Vtableidx5 = 0;
    CData/*4:0*/ __Vtableidx6;
    __Vtableidx6 = 0;
    CData/*4:0*/ __Vtableidx7;
    __Vtableidx7 = 0;
    CData/*7:0*/ __Vdly__top__DOT__u_keyboard_processor__DOT__key_buffer;
    __Vdly__top__DOT__u_keyboard_processor__DOT__key_buffer = 0;
    CData/*0:0*/ __Vdly__top__DOT__u_keyboard_processor__DOT__read_state;
    __Vdly__top__DOT__u_keyboard_processor__DOT__read_state = 0;
    // Body
    __Vdly__top__DOT__u_keyboard_processor__DOT__read_state 
        = vlSelf->top__DOT__u_keyboard_processor__DOT__read_state;
    __Vdly__top__DOT__u_keyboard_processor__DOT__key_buffer 
        = vlSelf->top__DOT__u_keyboard_processor__DOT__key_buffer;
    if (vlSelf->rst_n) {
        if (((IData)(vlSelf->top__DOT__ready) & (~ (IData)(vlSelf->top__DOT__u_keyboard_processor__DOT__read_state)))) {
            __Vdly__top__DOT__u_keyboard_processor__DOT__key_buffer 
                = vlSelf->top__DOT__u_ps2_keyboard__DOT__fifo
                [vlSelf->top__DOT__u_ps2_keyboard__DOT__r_ptr];
            vlSelf->top__DOT__nextdata_n = 0U;
            __Vdly__top__DOT__u_keyboard_processor__DOT__read_state = 1U;
        } else if (vlSelf->top__DOT__u_keyboard_processor__DOT__read_state) {
            vlSelf->top__DOT__nextdata_n = 1U;
            vlSelf->top__DOT__key_valid = 1U;
            __Vdly__top__DOT__u_keyboard_processor__DOT__read_state = 0U;
            vlSelf->top__DOT__key_pressed = (0xf0U 
                                             != (IData)(vlSelf->top__DOT__last_key));
            vlSelf->top__DOT__last_key = vlSelf->top__DOT__u_keyboard_processor__DOT__key_buffer;
            if ((0xf0U == (IData)(vlSelf->top__DOT__u_keyboard_processor__DOT__key_buffer))) {
                vlSelf->top__DOT__key_count = (0xffU 
                                               & ((IData)(1U) 
                                                  + (IData)(vlSelf->top__DOT__key_count)));
            }
        } else {
            vlSelf->top__DOT__key_valid = 0U;
        }
    } else {
        vlSelf->top__DOT__key_count = 0U;
        vlSelf->top__DOT__nextdata_n = 1U;
        __Vdly__top__DOT__u_keyboard_processor__DOT__key_buffer = 0U;
        vlSelf->top__DOT__last_key = 0U;
        vlSelf->top__DOT__key_valid = 0U;
        __Vdly__top__DOT__u_keyboard_processor__DOT__read_state = 0U;
        vlSelf->top__DOT__key_pressed = 0U;
    }
    vlSelf->top__DOT__u_keyboard_processor__DOT__key_buffer 
        = __Vdly__top__DOT__u_keyboard_processor__DOT__key_buffer;
    vlSelf->top__DOT__u_keyboard_processor__DOT__read_state 
        = __Vdly__top__DOT__u_keyboard_processor__DOT__read_state;
    __Vtableidx2 = (0xfU & ((IData)(vlSelf->top__DOT__key_count) 
                            >> 4U));
    vlSelf->top__DOT____Vcellout__u_seven_seg_decoder5__segments 
        = Vtop__ConstPool__TABLE_h25bdbd99_0[__Vtableidx2];
    __Vtableidx3 = (0xfU & (IData)(vlSelf->top__DOT__key_count));
    vlSelf->top__DOT____Vcellout__u_seven_seg_decoder4__segments 
        = Vtop__ConstPool__TABLE_h25bdbd99_0[__Vtableidx3];
    __Vtableidx6 = ((0x1eU & ((IData)(vlSelf->top__DOT__last_key) 
                              >> 3U)) | (IData)(vlSelf->top__DOT__key_pressed));
    vlSelf->top__DOT____Vcellout__u_seven_seg_decoder1__segments 
        = Vtop__ConstPool__TABLE_h99acd3d6_0[__Vtableidx6];
    __Vtableidx7 = ((0x1eU & ((IData)(vlSelf->top__DOT__last_key) 
                              << 1U)) | (IData)(vlSelf->top__DOT__key_pressed));
    vlSelf->top__DOT____Vcellout__u_seven_seg_decoder0__segments 
        = Vtop__ConstPool__TABLE_h99acd3d6_0[__Vtableidx7];
    __Vtableidx1 = vlSelf->top__DOT__last_key;
    vlSelf->top__DOT__ascii = Vtop__ConstPool__TABLE_h3b12cc5c_0
        [__Vtableidx1];
    vlSelf->seg5 = (1U | ((IData)(vlSelf->top__DOT____Vcellout__u_seven_seg_decoder5__segments) 
                          << 1U));
    vlSelf->seg4 = (1U | ((IData)(vlSelf->top__DOT____Vcellout__u_seven_seg_decoder4__segments) 
                          << 1U));
    vlSelf->seg1 = (1U | ((IData)(vlSelf->top__DOT____Vcellout__u_seven_seg_decoder1__segments) 
                          << 1U));
    vlSelf->seg0 = (1U | ((IData)(vlSelf->top__DOT____Vcellout__u_seven_seg_decoder0__segments) 
                          << 1U));
    __Vtableidx4 = ((0x1eU & ((IData)(vlSelf->top__DOT__ascii) 
                              >> 3U)) | (IData)(vlSelf->top__DOT__key_pressed));
    vlSelf->top__DOT____Vcellout__u_seven_seg_decoder3__segments 
        = Vtop__ConstPool__TABLE_h99acd3d6_0[__Vtableidx4];
    __Vtableidx5 = ((0x1eU & ((IData)(vlSelf->top__DOT__ascii) 
                              << 1U)) | (IData)(vlSelf->top__DOT__key_pressed));
    vlSelf->top__DOT____Vcellout__u_seven_seg_decoder2__segments 
        = Vtop__ConstPool__TABLE_h99acd3d6_0[__Vtableidx5];
    vlSelf->seg3 = (1U | ((IData)(vlSelf->top__DOT____Vcellout__u_seven_seg_decoder3__segments) 
                          << 1U));
    vlSelf->seg2 = (1U | ((IData)(vlSelf->top__DOT____Vcellout__u_seven_seg_decoder2__segments) 
                          << 1U));
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__2(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__2\n"); );
    // Body
    vlSelf->top__DOT__u_ps2_keyboard__DOT__r_ptr = vlSelf->__Vdly__top__DOT__u_ps2_keyboard__DOT__r_ptr;
    if (vlSelf->__Vdlyvset__top__DOT__u_ps2_keyboard__DOT__fifo__v0) {
        vlSelf->top__DOT__u_ps2_keyboard__DOT__fifo[vlSelf->__Vdlyvdim0__top__DOT__u_ps2_keyboard__DOT__fifo__v0] 
            = vlSelf->__Vdlyvval__top__DOT__u_ps2_keyboard__DOT__fifo__v0;
    }
    vlSelf->top__DOT__ready = vlSelf->__Vdly__top__DOT__ready;
}

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    // Body
    if (vlSelf->__VnbaTriggered.at(1U)) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[1U] = 1U;
    }
    if (vlSelf->__VnbaTriggered.at(0U)) {
        Vtop___024root___nba_sequent__TOP__1(vlSelf);
        vlSelf->__Vm_traceActivity[2U] = 1U;
    }
    if (vlSelf->__VnbaTriggered.at(1U)) {
        Vtop___024root___nba_sequent__TOP__2(vlSelf);
        vlSelf->__Vm_traceActivity[3U] = 1U;
    }
    if ((vlSelf->__VnbaTriggered.at(0U) | vlSelf->__VnbaTriggered.at(1U))) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

void Vtop___024root___eval_triggers__ico(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    // Init
    CData/*0:0*/ __VicoContinue;
    VlTriggerVec<2> __VpreTriggered;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    vlSelf->__VicoIterCount = 0U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        __VicoContinue = 0U;
        Vtop___024root___eval_triggers__ico(vlSelf);
        if (vlSelf->__VicoTriggered.any()) {
            __VicoContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VicoIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__ico(vlSelf);
#endif
                VL_FATAL_MT("/home/wizard/ysyx-workbench/npc/vsrc/top.v", 31, "", "Input combinational region did not converge.");
            }
            vlSelf->__VicoIterCount = ((IData)(1U) 
                                       + vlSelf->__VicoIterCount);
            Vtop___024root___eval_ico(vlSelf);
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
            Vtop___024root___eval_triggers__act(vlSelf);
            if (vlSelf->__VactTriggered.any()) {
                vlSelf->__VactContinue = 1U;
                if (VL_UNLIKELY((0x64U < vlSelf->__VactIterCount))) {
#ifdef VL_DEBUG
                    Vtop___024root___dump_triggers__act(vlSelf);
#endif
                    VL_FATAL_MT("/home/wizard/ysyx-workbench/npc/vsrc/top.v", 31, "", "Active region did not converge.");
                }
                vlSelf->__VactIterCount = ((IData)(1U) 
                                           + vlSelf->__VactIterCount);
                __VpreTriggered.andNot(vlSelf->__VactTriggered, vlSelf->__VnbaTriggered);
                vlSelf->__VnbaTriggered.set(vlSelf->__VactTriggered);
                Vtop___024root___eval_act(vlSelf);
            }
        }
        if (vlSelf->__VnbaTriggered.any()) {
            __VnbaContinue = 1U;
            if (VL_UNLIKELY((0x64U < __VnbaIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__nba(vlSelf);
#endif
                VL_FATAL_MT("/home/wizard/ysyx-workbench/npc/vsrc/top.v", 31, "", "NBA region did not converge.");
            }
            __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
            Vtop___024root___eval_nba(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((vlSelf->rst_n & 0xfeU))) {
        Verilated::overWidthError("rst_n");}
    if (VL_UNLIKELY((vlSelf->ps2_clk & 0xfeU))) {
        Verilated::overWidthError("ps2_clk");}
    if (VL_UNLIKELY((vlSelf->ps2_data & 0xfeU))) {
        Verilated::overWidthError("ps2_data");}
}
#endif  // VL_DEBUG
