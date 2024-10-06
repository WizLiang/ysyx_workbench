// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"

class Vtop__Syms;

class Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    VL_IN8(data_in,7,0);
    VL_IN8(ps2_clk,0,0);
    VL_IN8(ps2_data,0,0);
    VL_OUT8(seg5,7,0);
    VL_OUT8(seg4,7,0);
    VL_OUT8(seg3,7,0);
    VL_OUT8(seg2,7,0);
    VL_OUT8(seg1,7,0);
    VL_OUT8(seg0,7,0);
    CData/*0:0*/ top__DOT__ready;
    CData/*0:0*/ top__DOT__nextdata_n;
    CData/*7:0*/ top__DOT__last_key;
    CData/*0:0*/ top__DOT__key_valid;
    CData/*7:0*/ top__DOT__key_count;
    CData/*7:0*/ top__DOT__ascii;
    CData/*6:0*/ top__DOT____Vcellout__u_seven_seg_decoder5__segments;
    CData/*6:0*/ top__DOT____Vcellout__u_seven_seg_decoder4__segments;
    CData/*6:0*/ top__DOT____Vcellout__u_seven_seg_decoder3__segments;
    CData/*6:0*/ top__DOT____Vcellout__u_seven_seg_decoder2__segments;
    CData/*6:0*/ top__DOT____Vcellout__u_seven_seg_decoder1__segments;
    CData/*6:0*/ top__DOT____Vcellout__u_seven_seg_decoder0__segments;
    CData/*7:0*/ top__DOT__u_keyboard_processor__DOT__key_buffer;
    CData/*0:0*/ top__DOT__u_keyboard_processor__DOT__read_state;
    CData/*0:0*/ top__DOT__u_keyboard_processor__DOT__key_pressed;
    CData/*0:0*/ top__DOT__u_ps2_keyboard__DOT__overflow;
    CData/*2:0*/ top__DOT__u_ps2_keyboard__DOT__w_ptr;
    CData/*2:0*/ top__DOT__u_ps2_keyboard__DOT__r_ptr;
    CData/*3:0*/ top__DOT__u_ps2_keyboard__DOT__count;
    CData/*2:0*/ top__DOT__u_ps2_keyboard__DOT__ps2_clk_sync;
    CData/*0:0*/ top__DOT__u_ps2_keyboard__DOT____Vlvbound_h1a91ade8__0;
    CData/*2:0*/ __Vdly__top__DOT__u_ps2_keyboard__DOT__r_ptr;
    CData/*0:0*/ __Vdly__top__DOT__ready;
    CData/*2:0*/ __Vdlyvdim0__top__DOT__u_ps2_keyboard__DOT__fifo__v0;
    CData/*7:0*/ __Vdlyvval__top__DOT__u_ps2_keyboard__DOT__fifo__v0;
    CData/*0:0*/ __Vdlyvset__top__DOT__u_ps2_keyboard__DOT__fifo__v0;
    CData/*0:0*/ __Vtrigrprev__TOP__clk;
    CData/*0:0*/ __Vtrigrprev__TOP__rst_n;
    CData/*0:0*/ __VactContinue;
    VL_OUT16(led,15,0);
    SData/*9:0*/ top__DOT__u_ps2_keyboard__DOT__buffer;
    IData/*31:0*/ __VstlIterCount;
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<CData/*7:0*/, 8> top__DOT__u_ps2_keyboard__DOT__fifo;
    VlUnpacked<CData/*0:0*/, 4> __Vm_traceActivity;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);


#endif  // guard
