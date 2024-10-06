// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_fst_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_sub_0(Vtop___024root* vlSelf, VerilatedFst::Buffer* bufp);

void Vtop___024root__trace_chg_top_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_top_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vtop___024root__trace_chg_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_sub_0(Vtop___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[1U])) {
        bufp->chgBit(oldp+0,(vlSelf->top__DOT__u_ps2_keyboard__DOT__overflow));
        bufp->chgSData(oldp+1,(vlSelf->top__DOT__u_ps2_keyboard__DOT__buffer),10);
        bufp->chgCData(oldp+2,(vlSelf->top__DOT__u_ps2_keyboard__DOT__w_ptr),3);
        bufp->chgCData(oldp+3,(vlSelf->top__DOT__u_ps2_keyboard__DOT__count),4);
        bufp->chgCData(oldp+4,(vlSelf->top__DOT__u_ps2_keyboard__DOT__ps2_clk_sync),3);
        bufp->chgBit(oldp+5,((IData)((4U == (6U & (IData)(vlSelf->top__DOT__u_ps2_keyboard__DOT__ps2_clk_sync))))));
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[2U])) {
        bufp->chgBit(oldp+6,(vlSelf->top__DOT__nextdata_n));
        bufp->chgCData(oldp+7,(vlSelf->top__DOT__last_key),8);
        bufp->chgBit(oldp+8,(vlSelf->top__DOT__key_valid));
        bufp->chgCData(oldp+9,(vlSelf->top__DOT__key_count),8);
        bufp->chgCData(oldp+10,(vlSelf->top__DOT__ascii),8);
        bufp->chgCData(oldp+11,(vlSelf->top__DOT__u_keyboard_processor__DOT__key_buffer),8);
        bufp->chgBit(oldp+12,(vlSelf->top__DOT__u_keyboard_processor__DOT__read_state));
        bufp->chgBit(oldp+13,(vlSelf->top__DOT__u_keyboard_processor__DOT__key_pressed));
        bufp->chgCData(oldp+14,((0xfU & (IData)(vlSelf->top__DOT__last_key))),4);
        bufp->chgCData(oldp+15,(vlSelf->top__DOT____Vcellout__u_seven_seg_decoder0__segments),7);
        bufp->chgCData(oldp+16,((0xfU & ((IData)(vlSelf->top__DOT__last_key) 
                                         >> 4U))),4);
        bufp->chgCData(oldp+17,(vlSelf->top__DOT____Vcellout__u_seven_seg_decoder1__segments),7);
        bufp->chgCData(oldp+18,((0xfU & (IData)(vlSelf->top__DOT__ascii))),4);
        bufp->chgCData(oldp+19,(vlSelf->top__DOT____Vcellout__u_seven_seg_decoder2__segments),7);
        bufp->chgCData(oldp+20,((0xfU & ((IData)(vlSelf->top__DOT__ascii) 
                                         >> 4U))),4);
        bufp->chgCData(oldp+21,(vlSelf->top__DOT____Vcellout__u_seven_seg_decoder3__segments),7);
        bufp->chgCData(oldp+22,((0xfU & (IData)(vlSelf->top__DOT__key_count))),4);
        bufp->chgCData(oldp+23,(vlSelf->top__DOT____Vcellout__u_seven_seg_decoder4__segments),7);
        bufp->chgCData(oldp+24,((0xfU & ((IData)(vlSelf->top__DOT__key_count) 
                                         >> 4U))),4);
        bufp->chgCData(oldp+25,(vlSelf->top__DOT____Vcellout__u_seven_seg_decoder5__segments),7);
    }
    if (VL_UNLIKELY(vlSelf->__Vm_traceActivity[3U])) {
        bufp->chgBit(oldp+26,(vlSelf->top__DOT__ready));
        bufp->chgCData(oldp+27,(vlSelf->top__DOT__u_ps2_keyboard__DOT__fifo
                                [vlSelf->top__DOT__u_ps2_keyboard__DOT__r_ptr]),8);
        bufp->chgCData(oldp+28,(vlSelf->top__DOT__u_ps2_keyboard__DOT__fifo[0]),8);
        bufp->chgCData(oldp+29,(vlSelf->top__DOT__u_ps2_keyboard__DOT__fifo[1]),8);
        bufp->chgCData(oldp+30,(vlSelf->top__DOT__u_ps2_keyboard__DOT__fifo[2]),8);
        bufp->chgCData(oldp+31,(vlSelf->top__DOT__u_ps2_keyboard__DOT__fifo[3]),8);
        bufp->chgCData(oldp+32,(vlSelf->top__DOT__u_ps2_keyboard__DOT__fifo[4]),8);
        bufp->chgCData(oldp+33,(vlSelf->top__DOT__u_ps2_keyboard__DOT__fifo[5]),8);
        bufp->chgCData(oldp+34,(vlSelf->top__DOT__u_ps2_keyboard__DOT__fifo[6]),8);
        bufp->chgCData(oldp+35,(vlSelf->top__DOT__u_ps2_keyboard__DOT__fifo[7]),8);
        bufp->chgCData(oldp+36,(vlSelf->top__DOT__u_ps2_keyboard__DOT__r_ptr),3);
    }
    bufp->chgBit(oldp+37,(vlSelf->clk));
    bufp->chgBit(oldp+38,(vlSelf->rst_n));
    bufp->chgCData(oldp+39,(vlSelf->data_in),8);
    bufp->chgBit(oldp+40,(vlSelf->ps2_clk));
    bufp->chgBit(oldp+41,(vlSelf->ps2_data));
    bufp->chgCData(oldp+42,(vlSelf->seg5),8);
    bufp->chgCData(oldp+43,(vlSelf->seg4),8);
    bufp->chgCData(oldp+44,(vlSelf->seg3),8);
    bufp->chgCData(oldp+45,(vlSelf->seg2),8);
    bufp->chgCData(oldp+46,(vlSelf->seg1),8);
    bufp->chgCData(oldp+47,(vlSelf->seg0),8);
    bufp->chgSData(oldp+48,(vlSelf->led),16);
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[3U] = 0U;
}
