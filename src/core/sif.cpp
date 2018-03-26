#include <cstdio>
#include "sif.hpp"

/**
 * TODO: What are the sizes of the SIF0/SIF1 DMAC FIFOs?
 */

SubsystemInterface::SubsystemInterface()
{

}

void SubsystemInterface::reset()
{
    std::queue<uint32_t> empty, empty2;
    SIF0_FIFO.swap(empty);
    SIF1_FIFO.swap(empty2);
    mscom = 0;
    smcom = 0;
    msflag = 0;
    smflag = 0;
    control = 0;
}

int SubsystemInterface::get_SIF0_size()
{
    return SIF0_FIFO.size();
}

int SubsystemInterface::get_SIF1_size()
{
    return SIF1_FIFO.size();
}

void SubsystemInterface::write_SIF0(uint32_t word)
{
    SIF0_FIFO.push(word);
    printf("[SIF0] Word: $%08X\n", word);
}

void SubsystemInterface::write_SIF1(uint64_t *quad)
{
    SIF1_FIFO.push(quad[0] & 0xFFFFFFFF);
    SIF1_FIFO.push(quad[0] >> 32);
    SIF1_FIFO.push(quad[1] & 0xFFFFFFFF);
    SIF1_FIFO.push(quad[1] >> 32);
    printf("[SIF1] Quad: $%08X_%08X_%08X_%08X\n", quad[1] >> 32, quad[1], quad[0] >> 32, quad[0]);
}

uint32_t SubsystemInterface::read_SIF0()
{
    uint32_t value = SIF0_FIFO.front();
    SIF0_FIFO.pop();
    return value;
}

uint32_t SubsystemInterface::read_SIF1()
{
    uint32_t value = SIF1_FIFO.front();
    SIF1_FIFO.pop();
    return value;
}

uint32_t SubsystemInterface::get_mscom()
{
    return mscom;
}

uint32_t SubsystemInterface::get_smcom()
{
    return smcom;
}

uint32_t SubsystemInterface::get_msflag()
{
    return msflag;
}

uint32_t SubsystemInterface::get_smflag()
{
    return smflag;
}

uint32_t SubsystemInterface::get_control()
{
    return control;
}

void SubsystemInterface::set_mscom(uint32_t value)
{
    mscom = value;
}

void SubsystemInterface::set_smcom(uint32_t value)
{
    smcom = value;
}

void SubsystemInterface::set_msflag(uint32_t value)
{
    msflag |= value;
}

void SubsystemInterface::reset_msflag(uint32_t value)
{
    msflag &= ~value;
}

void SubsystemInterface::set_smflag(uint32_t value)
{
    smflag |= value;
}

void SubsystemInterface::reset_smflag(uint32_t value)
{
    smflag &= ~value;
}

void SubsystemInterface::set_control_EE(uint32_t value)
{
    if (!(value & 0x100))
        control &= ~0x100;
    else
        control |= 0x100;
}

void SubsystemInterface::set_control_IOP(uint32_t value)
{

}
