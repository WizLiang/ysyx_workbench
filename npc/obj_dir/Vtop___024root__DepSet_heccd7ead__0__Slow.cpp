// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "verilated.h"

#include "Vtop___024root.h"

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vtrigrprev__TOP__clk = vlSelf->clk;
    vlSelf->__Vtrigrprev__TOP__rst_n = vlSelf->rst_n;
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
}

VL_ATTR_COLD void Vtop___024root___eval_triggers__stl(Vtop___024root* vlSelf);
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    // Init
    CData/*0:0*/ __VstlContinue;
    // Body
    vlSelf->__VstlIterCount = 0U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        __VstlContinue = 0U;
        Vtop___024root___eval_triggers__stl(vlSelf);
        if (vlSelf->__VstlTriggered.any()) {
            __VstlContinue = 1U;
            if (VL_UNLIKELY((0x64U < vlSelf->__VstlIterCount))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__stl(vlSelf);
#endif
                VL_FATAL_MT("/home/wizard/ysyx-workbench/npc/vsrc/top.v", 31, "", "Settle region did not converge.");
            }
            vlSelf->__VstlIterCount = ((IData)(1U) 
                                       + vlSelf->__VstlIterCount);
            Vtop___024root___eval_stl(vlSelf);
        }
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VstlTriggered.at(0U)) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

extern const VlUnpacked<CData/*6:0*/, 16> Vtop__ConstPool__TABLE_h25bdbd99_0;
extern const VlUnpacked<CData/*6:0*/, 32> Vtop__ConstPool__TABLE_h99acd3d6_0;
extern const VlUnpacked<CData/*7:0*/, 256> Vtop__ConstPool__TABLE_h3b12cc5c_0;

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___stl_sequent__TOP__0\n"); );
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

VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    // Body
    if (vlSelf->__VstlTriggered.at(0U)) {
        Vtop___024root___stl_sequent__TOP__0(vlSelf);
        vlSelf->__Vm_traceActivity[3U] = 1U;
        vlSelf->__Vm_traceActivity[2U] = 1U;
        vlSelf->__Vm_traceActivity[1U] = 1U;
        vlSelf->__Vm_traceActivity[0U] = 1U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__ico\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VicoTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VicoTriggered.at(0U)) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VactTriggered.at(0U)) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk or negedge rst_n)\n");
    }
    if (vlSelf->__VactTriggered.at(1U)) {
        VL_DBG_MSGF("         'act' region trigger index 1 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if (vlSelf->__VnbaTriggered.at(0U)) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk or negedge rst_n)\n");
    }
    if (vlSelf->__VnbaTriggered.at(1U)) {
        VL_DBG_MSGF("         'nba' region trigger index 1 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->rst_n = VL_RAND_RESET_I(1);
    vlSelf->data_in = VL_RAND_RESET_I(8);
    vlSelf->ps2_clk = VL_RAND_RESET_I(1);
    vlSelf->ps2_data = VL_RAND_RESET_I(1);
    vlSelf->seg5 = VL_RAND_RESET_I(8);
    vlSelf->seg4 = VL_RAND_RESET_I(8);
    vlSelf->seg3 = VL_RAND_RESET_I(8);
    vlSelf->seg2 = VL_RAND_RESET_I(8);
    vlSelf->seg1 = VL_RAND_RESET_I(8);
    vlSelf->seg0 = VL_RAND_RESET_I(8);
    vlSelf->led = VL_RAND_RESET_I(16);
    vlSelf->top__DOT__ready = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__nextdata_n = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__last_key = VL_RAND_RESET_I(8);
    vlSelf->top__DOT__key_valid = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__key_pressed = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__key_count = VL_RAND_RESET_I(8);
    vlSelf->top__DOT__ascii = VL_RAND_RESET_I(8);
    vlSelf->top__DOT__overflow = VL_RAND_RESET_I(1);
    vlSelf->top__DOT____Vcellout__u_seven_seg_decoder5__segments = VL_RAND_RESET_I(7);
    vlSelf->top__DOT____Vcellout__u_seven_seg_decoder4__segments = VL_RAND_RESET_I(7);
    vlSelf->top__DOT____Vcellout__u_seven_seg_decoder3__segments = VL_RAND_RESET_I(7);
    vlSelf->top__DOT____Vcellout__u_seven_seg_decoder2__segments = VL_RAND_RESET_I(7);
    vlSelf->top__DOT____Vcellout__u_seven_seg_decoder1__segments = VL_RAND_RESET_I(7);
    vlSelf->top__DOT____Vcellout__u_seven_seg_decoder0__segments = VL_RAND_RESET_I(7);
    vlSelf->top__DOT__u_keyboard_processor__DOT__key_buffer = VL_RAND_RESET_I(8);
    vlSelf->top__DOT__u_keyboard_processor__DOT__read_state = VL_RAND_RESET_I(1);
    vlSelf->top__DOT__u_ps2_keyboard__DOT__buffer = VL_RAND_RESET_I(10);
    for (int __Vi0 = 0; __Vi0 < 8; ++__Vi0) {
        vlSelf->top__DOT__u_ps2_keyboard__DOT__fifo[__Vi0] = VL_RAND_RESET_I(8);
    }
    vlSelf->top__DOT__u_ps2_keyboard__DOT__w_ptr = VL_RAND_RESET_I(3);
    vlSelf->top__DOT__u_ps2_keyboard__DOT__r_ptr = VL_RAND_RESET_I(3);
    vlSelf->top__DOT__u_ps2_keyboard__DOT__count = VL_RAND_RESET_I(4);
    vlSelf->top__DOT__u_ps2_keyboard__DOT__ps2_clk_sync = VL_RAND_RESET_I(3);
    vlSelf->top__DOT__u_ps2_keyboard__DOT____Vlvbound_h1a91ade8__0 = VL_RAND_RESET_I(1);
    vlSelf->__Vdly__top__DOT__u_ps2_keyboard__DOT__r_ptr = VL_RAND_RESET_I(3);
    vlSelf->__Vdly__top__DOT__ready = VL_RAND_RESET_I(1);
    vlSelf->__Vdlyvdim0__top__DOT__u_ps2_keyboard__DOT__fifo__v0 = 0;
    vlSelf->__Vdlyvval__top__DOT__u_ps2_keyboard__DOT__fifo__v0 = VL_RAND_RESET_I(8);
    vlSelf->__Vdlyvset__top__DOT__u_ps2_keyboard__DOT__fifo__v0 = 0;
    vlSelf->__Vtrigrprev__TOP__clk = VL_RAND_RESET_I(1);
    vlSelf->__Vtrigrprev__TOP__rst_n = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
