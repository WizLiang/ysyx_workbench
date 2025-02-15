// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_fst_c.h"
#include "Vcpu_top__Syms.h"


VL_ATTR_COLD void Vcpu_top___024root__trace_init_sub__TOP__0(Vcpu_top___024root* vlSelf, VerilatedFst* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_top___024root__trace_init_sub__TOP__0\n"); );
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->declBit(c+34,"clk",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBit(c+35,"rst",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBus(c+36,"inst",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declBus(c+37,"pc",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->pushNamePrefix("cpu_top ");
    tracep->declBus(c+50,"ADDR_WIDTH",-1, FST_VD_IMPLICIT,FST_VT_VCD_PARAMETER, false,-1, 31,0);
    tracep->declBus(c+51,"DATA_WIDTH",-1, FST_VD_IMPLICIT,FST_VT_VCD_PARAMETER, false,-1, 31,0);
    tracep->declBit(c+34,"clk",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBit(c+35,"rst",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBus(c+36,"inst",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declBus(c+37,"pc",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declBus(c+38,"imm",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declBus(c+39,"rs1_data",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declBus(c+40,"rs2_data",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declBus(c+41,"rd_data",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declBus(c+42,"rs1_addr",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declBus(c+43,"rs2_addr",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declBus(c+44,"rd_addr",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declBus(c+44,"rd_tmp",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declBit(c+45,"is_I_type",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBit(c+52,"is_R_type",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBus(c+46,"func3",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 2,0);
    tracep->declBus(c+47,"func7",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 6,0);
    tracep->declBus(c+48,"opcode",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1, 6,0);
    tracep->declBit(c+49,"wr_en_reg",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1);
    tracep->pushNamePrefix("u_EXU ");
    tracep->declBus(c+50,"ADDR_WIDTH",-1, FST_VD_IMPLICIT,FST_VT_VCD_PARAMETER, false,-1, 31,0);
    tracep->declBus(c+51,"DATA_WIDTH",-1, FST_VD_IMPLICIT,FST_VT_VCD_PARAMETER, false,-1, 31,0);
    tracep->declBus(c+46,"func3",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 2,0);
    tracep->declBus(c+47,"func7",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 6,0);
    tracep->declBus(c+48,"opcode",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 6,0);
    tracep->declBit(c+45,"is_I_type",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBit(c+52,"is_R_type",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBus(c+39,"rs1",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declBus(c+40,"rs2",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declBus(c+38,"imm",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declBus(c+44,"rd",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declBit(c+49,"wr_en",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBus(c+44,"waddr",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declBus(c+41,"wdata",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declBit(c+49,"addi",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBit(c+45,"op_imm",-1, FST_VD_IMPLICIT,FST_VT_VCD_WIRE, false,-1);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_IDU ");
    tracep->declBus(c+50,"ADDR_WIDTH",-1, FST_VD_IMPLICIT,FST_VT_VCD_PARAMETER, false,-1, 31,0);
    tracep->declBus(c+51,"DATA_WIDTH",-1, FST_VD_IMPLICIT,FST_VT_VCD_PARAMETER, false,-1, 31,0);
    tracep->declBus(c+36,"inst",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declBus(c+38,"imm",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declBus(c+42,"rs1",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declBus(c+43,"rs2",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declBus(c+44,"rd",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declBit(c+45,"is_I_type",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBit(c+52,"is_R_type",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBus(c+46,"func3",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 2,0);
    tracep->declBus(c+47,"func7",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 6,0);
    tracep->declBus(c+48,"opcode",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 6,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_pc ");
    tracep->declBus(c+51,"PC_WIDTH",-1, FST_VD_IMPLICIT,FST_VT_VCD_PARAMETER, false,-1, 31,0);
    tracep->declBus(c+53,"PC_RESET",-1, FST_VD_IMPLICIT,FST_VT_VCD_PARAMETER, false,-1, 31,0);
    tracep->declBit(c+34,"clk",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBit(c+35,"rst",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBit(c+54,"en",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBus(c+53,"pc_in",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declBus(c+37,"pc_out",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->popNamePrefix(1);
    tracep->pushNamePrefix("u_rf ");
    tracep->declBus(c+51,"DATA_WIDTH",-1, FST_VD_IMPLICIT,FST_VT_VCD_PARAMETER, false,-1, 31,0);
    tracep->declBus(c+50,"ADDR_WIDTH",-1, FST_VD_IMPLICIT,FST_VT_VCD_PARAMETER, false,-1, 31,0);
    tracep->declBit(c+34,"clk",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBit(c+35,"rst",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBus(c+42,"raddr1",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declBus(c+39,"rdata1",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declBus(c+43,"raddr2",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declBus(c+40,"rdata2",-1,FST_VD_OUTPUT,FST_VT_VCD_WIRE, false,-1, 31,0);
    tracep->declBus(c+44,"waddr",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 4,0);
    tracep->declBit(c+49,"wr_en",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1);
    tracep->declBus(c+41,"wdata",-1,FST_VD_INPUT,FST_VT_VCD_WIRE, false,-1, 31,0);
    for (int i = 0; i < 32; ++i) {
        tracep->declBus(c+1+i*1,"gpr",-1, FST_VD_IMPLICIT,FST_VT_SV_LOGIC, true,(i+0), 31,0);
    }
    tracep->pushNamePrefix("unnamedblk1 ");
    tracep->declBus(c+33,"i",-1, FST_VD_IMPLICIT,FST_VT_VCD_INTEGER, false,-1, 31,0);
    tracep->popNamePrefix(3);
}

VL_ATTR_COLD void Vcpu_top___024root__trace_init_top(Vcpu_top___024root* vlSelf, VerilatedFst* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_top___024root__trace_init_top\n"); );
    // Body
    Vcpu_top___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vcpu_top___024root__trace_full_top_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vcpu_top___024root__trace_chg_top_0(void* voidSelf, VerilatedFst::Buffer* bufp);
void Vcpu_top___024root__trace_cleanup(void* voidSelf, VerilatedFst* /*unused*/);

VL_ATTR_COLD void Vcpu_top___024root__trace_register(Vcpu_top___024root* vlSelf, VerilatedFst* tracep) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_top___024root__trace_register\n"); );
    // Body
    tracep->addFullCb(&Vcpu_top___024root__trace_full_top_0, vlSelf);
    tracep->addChgCb(&Vcpu_top___024root__trace_chg_top_0, vlSelf);
    tracep->addCleanupCb(&Vcpu_top___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vcpu_top___024root__trace_full_sub_0(Vcpu_top___024root* vlSelf, VerilatedFst::Buffer* bufp);

VL_ATTR_COLD void Vcpu_top___024root__trace_full_top_0(void* voidSelf, VerilatedFst::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_top___024root__trace_full_top_0\n"); );
    // Init
    Vcpu_top___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vcpu_top___024root*>(voidSelf);
    Vcpu_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vcpu_top___024root__trace_full_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vcpu_top___024root__trace_full_sub_0(Vcpu_top___024root* vlSelf, VerilatedFst::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vcpu_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vcpu_top___024root__trace_full_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+1,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[0]),32);
    bufp->fullIData(oldp+2,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[1]),32);
    bufp->fullIData(oldp+3,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[2]),32);
    bufp->fullIData(oldp+4,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[3]),32);
    bufp->fullIData(oldp+5,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[4]),32);
    bufp->fullIData(oldp+6,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[5]),32);
    bufp->fullIData(oldp+7,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[6]),32);
    bufp->fullIData(oldp+8,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[7]),32);
    bufp->fullIData(oldp+9,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[8]),32);
    bufp->fullIData(oldp+10,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[9]),32);
    bufp->fullIData(oldp+11,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[10]),32);
    bufp->fullIData(oldp+12,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[11]),32);
    bufp->fullIData(oldp+13,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[12]),32);
    bufp->fullIData(oldp+14,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[13]),32);
    bufp->fullIData(oldp+15,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[14]),32);
    bufp->fullIData(oldp+16,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[15]),32);
    bufp->fullIData(oldp+17,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[16]),32);
    bufp->fullIData(oldp+18,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[17]),32);
    bufp->fullIData(oldp+19,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[18]),32);
    bufp->fullIData(oldp+20,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[19]),32);
    bufp->fullIData(oldp+21,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[20]),32);
    bufp->fullIData(oldp+22,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[21]),32);
    bufp->fullIData(oldp+23,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[22]),32);
    bufp->fullIData(oldp+24,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[23]),32);
    bufp->fullIData(oldp+25,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[24]),32);
    bufp->fullIData(oldp+26,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[25]),32);
    bufp->fullIData(oldp+27,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[26]),32);
    bufp->fullIData(oldp+28,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[27]),32);
    bufp->fullIData(oldp+29,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[28]),32);
    bufp->fullIData(oldp+30,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[29]),32);
    bufp->fullIData(oldp+31,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[30]),32);
    bufp->fullIData(oldp+32,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr[31]),32);
    bufp->fullIData(oldp+33,(vlSelf->cpu_top__DOT__u_rf__DOT__unnamedblk1__DOT__i),32);
    bufp->fullBit(oldp+34,(vlSelf->clk));
    bufp->fullBit(oldp+35,(vlSelf->rst));
    bufp->fullIData(oldp+36,(vlSelf->inst),32);
    bufp->fullIData(oldp+37,(vlSelf->pc),32);
    bufp->fullIData(oldp+38,(((0x13U == (0x7fU & vlSelf->inst))
                               ? (((- (IData)((vlSelf->inst 
                                               >> 0x1fU))) 
                                   << 0xcU) | (vlSelf->inst 
                                               >> 0x14U))
                               : 0U)),32);
    bufp->fullIData(oldp+39,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr
                             [(0x1fU & (vlSelf->inst 
                                        >> 0xfU))]),32);
    bufp->fullIData(oldp+40,(vlSelf->cpu_top__DOT__u_rf__DOT__gpr
                             [(0x1fU & (vlSelf->inst 
                                        >> 0x14U))]),32);
    bufp->fullIData(oldp+41,(((IData)(vlSelf->cpu_top__DOT__wr_en_reg)
                               ? (((0x13U == (0x7fU 
                                              & vlSelf->inst))
                                    ? (((- (IData)(
                                                   (vlSelf->inst 
                                                    >> 0x1fU))) 
                                        << 0xcU) | 
                                       (vlSelf->inst 
                                        >> 0x14U)) : 0U) 
                                  + vlSelf->cpu_top__DOT__u_rf__DOT__gpr
                                  [(0x1fU & (vlSelf->inst 
                                             >> 0xfU))])
                               : 0U)),32);
    bufp->fullCData(oldp+42,((0x1fU & (vlSelf->inst 
                                       >> 0xfU))),5);
    bufp->fullCData(oldp+43,((0x1fU & (vlSelf->inst 
                                       >> 0x14U))),5);
    bufp->fullCData(oldp+44,((0x1fU & (vlSelf->inst 
                                       >> 7U))),5);
    bufp->fullBit(oldp+45,((0x13U == (0x7fU & vlSelf->inst))));
    bufp->fullCData(oldp+46,((7U & (vlSelf->inst >> 0xcU))),3);
    bufp->fullCData(oldp+47,((vlSelf->inst >> 0x19U)),7);
    bufp->fullCData(oldp+48,((0x7fU & vlSelf->inst)),7);
    bufp->fullBit(oldp+49,(vlSelf->cpu_top__DOT__wr_en_reg));
    bufp->fullIData(oldp+50,(5U),32);
    bufp->fullIData(oldp+51,(0x20U),32);
    bufp->fullBit(oldp+52,(vlSelf->cpu_top__DOT__is_R_type));
    bufp->fullIData(oldp+53,(0x80000000U),32);
    bufp->fullBit(oldp+54,(0U));
}
