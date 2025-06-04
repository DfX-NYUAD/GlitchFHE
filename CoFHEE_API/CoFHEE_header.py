
SRAM_BASE    = "20000000"
FHEMEM0_BASE = "21000000"
FHEMEM1_BASE = "22000000"
FHEMEM2_BASE = "23000000"
FHEMEM3_BASE = "24000000"
FHEMEM4_BASE = "25000000"
FHEMEM5_BASE = "26000000"
FHEMEM6_BASE = "27000000"

FHEMEM0_DP_BASE = "31000000"
FHEMEM1_DP_BASE = "32000000"
FHEMEM2_DP_BASE = "33000000"

GPCFG_BASE    = "42000000"
GPIO_BASE     = "43000000"
MULTPOOL_BASE = "46000000"


SRAM_ADDR0   = str(hex(int(SRAM_BASE, 16) + int("0000", 16)))
SRAM_ADDR0   = SRAM_ADDR0[2:]

FHEMEM0_ADDR0   = str(hex(int(FHEMEM0_BASE, 16) + int("0000", 16)))
FHEMEM0_ADDR0   = FHEMEM0_ADDR0[2:]

FHEMEM1_ADDR0   = str(hex(int(FHEMEM1_BASE, 16) + int("0000", 16)))
FHEMEM1_ADDR0   = FHEMEM1_ADDR0[2:]

FHEMEM2_ADDR0   = str(hex(int(FHEMEM2_BASE, 16) + int("0000", 16)))
FHEMEM2_ADDR0   = FHEMEM2_ADDR0[2:]

FHEMEM3_ADDR0   = str(hex(int(FHEMEM3_BASE, 16) + int("0000", 16)))
FHEMEM3_ADDR0   = FHEMEM3_ADDR0[2:]

FHEMEM4_ADDR0   = str(hex(int(FHEMEM4_BASE, 16) + int("0000", 16)))
FHEMEM4_ADDR0   = FHEMEM4_ADDR0[2:]

FHEMEM5_ADDR0   = str(hex(int(FHEMEM5_BASE, 16) + int("0000", 16)))
FHEMEM5_ADDR0   = FHEMEM5_ADDR0[2:]

FHEMEM6_ADDR0   = str(hex(int(FHEMEM6_BASE, 16) + int("0000", 16)))
FHEMEM6_ADDR0   = FHEMEM6_ADDR0[2:]

GPCFG_UARTMTX_PAD_CTL   = str(hex(int(GPCFG_BASE, 16) + int("0000", 16)))
GPCFG_UARTMTX_PAD_CTL   = GPCFG_UARTMTX_PAD_CTL[2:]
GPCFG_UARTMRX_PAD_CTL   = str(hex(int(GPCFG_BASE, 16) + int("0004", 16)))
GPCFG_UARTMRX_PAD_CTL   = GPCFG_UARTMRX_PAD_CTL[2:]
GPCFG_UARTSTX_PAD_CTL   = str(hex(int(GPCFG_BASE, 16) + int("0008", 16)))
GPCFG_UARTSTX_PAD_CTL   = GPCFG_UARTSTX_PAD_CTL[2:]
GPCFG_UARTSRX_PAD_CTL   = str(hex(int(GPCFG_BASE, 16) + int("000C", 16)))
GPCFG_UARTSRX_PAD_CTL   = GPCFG_UARTSRX_PAD_CTL[2:]
GPCFG_SPICLK_PAD_CTL    = str(hex(int(GPCFG_BASE, 16) + int("0010", 16)))
GPCFG_SPICLK_PAD_CTL    = GPCFG_SPICLK_PAD_CTL[2:]
GPCFG_SPICSN_PAD_CTL    = str(hex(int(GPCFG_BASE, 16) + int("0014", 16)))
GPCFG_SPICSN_PAD_CTL    = GPCFG_SPICSN_PAD_CTL[2:]
GPCFG_HOSTIRQ_PAD_CTL   = str(hex(int(GPCFG_BASE, 16) + int("0018", 16)))
GPCFG_HOSTIRQ_PAD_CTL   = GPCFG_HOSTIRQ_PAD_CTL[2:]
GPCFG_GPIO0_PAD_CTL     = str(hex(int(GPCFG_BASE, 16) + int("001C", 16)))
GPCFG_GPIO0_PAD_CTL     = GPCFG_GPIO0_PAD_CTL[2:]
GPCFG_PAD11_PAD_CTL     = str(hex(int(GPCFG_BASE, 16) + int("0020", 16)))
GPCFG_PAD11_PAD_CTL     = GPCFG_PAD11_PAD_CTL[2:]
GPCFG_PAD12_PAD_CTL     = str(hex(int(GPCFG_BASE, 16) + int("0024", 16)))
GPCFG_PAD12_PAD_CTL     = GPCFG_PAD12_PAD_CTL[2:]
GPCFG_PAD13_PAD_CTL     = str(hex(int(GPCFG_BASE, 16) + int("0028", 16)))
GPCFG_PAD13_PAD_CTL     = GPCFG_PAD13_PAD_CTL[2:]
GPCFG_PAD14_PAD_CTL     = str(hex(int(GPCFG_BASE, 16) + int("002c", 16)))
GPCFG_PAD14_PAD_CTL     = GPCFG_PAD14_PAD_CTL[2:]
GPCFG_PAD15_PAD_CTL     = str(hex(int(GPCFG_BASE, 16) + int("0030", 16)))
GPCFG_PAD15_PAD_CTL     = GPCFG_PAD15_PAD_CTL[2:]
GPCFG_PAD16_PAD_CTL     = str(hex(int(GPCFG_BASE, 16) + int("0034", 16)))
GPCFG_PAD16_PAD_CTL     = GPCFG_PAD16_PAD_CTL[2:]
GPCFG_PAD17_PAD_CTL     = str(hex(int(GPCFG_BASE, 16) + int("0038", 16)))
GPCFG_PAD17_PAD_CTL     = GPCFG_PAD17_PAD_CTL[2:]
GPCFG_PAD18_PAD_CTL     = str(hex(int(GPCFG_BASE, 16) + int("003c", 16)))
GPCFG_PAD18_PAD_CTL     = GPCFG_PAD18_PAD_CTL[2:]
GPCFG_PAD19_PAD_CTL     = str(hex(int(GPCFG_BASE, 16) + int("0040", 16)))
GPCFG_PAD19_PAD_CTL     = GPCFG_PAD19_PAD_CTL[2:]

GPCFG_SFLL0_ADDR        = str(hex(int(GPCFG_BASE, 16) + int("00AC", 16)))
GPCFG_SFLL0_ADDR        = GPCFG_SFLL0_ADDR[2:]
GPCFG_SFLL1_ADDR        = str(hex(int(GPCFG_BASE, 16) + int("00B0", 16)))
GPCFG_SFLL1_ADDR        = GPCFG_SFLL1_ADDR[2:]
GPCFG_SFLL2_ADDR        = str(hex(int(GPCFG_BASE, 16) + int("00B4", 16)))
GPCFG_SFLL2_ADDR        = GPCFG_SFLL2_ADDR[2:]
GPCFG_SFLL3_ADDR        = str(hex(int(GPCFG_BASE, 16) + int("00B8", 16)))
GPCFG_SFLL3_ADDR        = GPCFG_SFLL3_ADDR[2:]

GPCFG_FLL0_ADDR        = str(hex(int(GPCFG_BASE, 16) + int("00BC", 16)))
GPCFG_FLL0_ADDR        = GPCFG_FLL0_ADDR[2:]
GPCFG_FLL1_ADDR        = str(hex(int(GPCFG_BASE, 16) + int("00C0", 16)))
GPCFG_FLL1_ADDR        = GPCFG_FLL1_ADDR[2:]
GPCFG_FLL2_ADDR        = str(hex(int(GPCFG_BASE, 16) + int("00C4", 16)))
GPCFG_FLL2_ADDR        = GPCFG_FLL2_ADDR[2:]
GPCFG_FLL3_ADDR        = str(hex(int(GPCFG_BASE, 16) + int("00C8", 16)))
GPCFG_FLL3_ADDR        = GPCFG_FLL3_ADDR[2:]


#//Bits in GPCG_*PADCT
#define  PADOEN      (1U << 0)      //0 = > Output enabled, 1 => HiZ,pull up or pull down depends on pull setting
#define  PADRXEN     (1U << 1)      //0 = > Input disabled, 1 => Input Enabled
#define  PADPULL0    (1U << 2)      //00 => HiZ, 01 => Pull Up, 10 => Pull down, 11 => Repeater
#define  PADPULL1    (1U << 3)      //00 => HiZ, 01 => Pull Up, 10 => Pull down, 11 => Repeater
#define  PADPULL2    (1U << 2)      //00 => HiZ, 01 => Pull Up, 10 => Pull down, 11 => Repeater
#define  PADDRIVE0   (1U << 4)      //00 => 2mA, 01 => 4mA,     10 => 8mA,       11 => 12mA
#define  PADDRIVE1   (1U << 4)      //00 => 2mA, 01 => 4mA,     10 => 8mA,       11 => 12mA
#define  PADSCHMITT  (1U << 6)      //0  => Scmitt Disabled.       1 => Enabled
#define  PADSLEW     (1U << 7)      //0  => Slow (half frequency). 1 => Fast
#define  PADPOSCTL   (1U << 8)      //0  => PAD is in hig-Z due to loss of core power.
                                   #//1  => PAD is pulled down. This happens when core supply is not there.
#define  ALTFUNCSEL0  (1U << 16)   //
#define  ALTFUNCSEL1  (1U << 17)   //
#define  ALTFUNCGPIO  (1U << 24)   //




GPCFG_UARTM_BAUD_CTL    = str(hex(int(GPCFG_BASE, 16) + int("0044", 16)))
GPCFG_UARTM_BAUD_CTL    = GPCFG_UARTM_BAUD_CTL[2:]
GPCFG_UARTS_BAUD_CTL    = str(hex(int(GPCFG_BASE, 16) + int("0088", 16)))
GPCFG_UARTS_BAUD_CTL    = GPCFG_UARTS_BAUD_CTL[2:]

GPCFG_UARTM_CTL         = str(hex(int(GPCFG_BASE, 16) + int("0048", 16)))
GPCFG_UARTM_CTL         = GPCFG_UARTM_CTL[2:]
GPCFG_UARTS_CTL         = str(hex(int(GPCFG_BASE, 16) + int("008c", 16)))
GPCFG_UARTS_CTL         = GPCFG_UARTS_CTL[2:]

#define  UARTMDWIDTH0       (1U << 0)     //00 => 1 byte, 01 => 2 byte, 10 => 4 byte, 11 => 1 byte
#define  UARTMDWIDTH1       (1U << 1)     //00 => 1 byte, 01 => 2 byte, 10 => 4 byte, 11 => 1 byte
#define  UARTMPARTEN        (1U << 2)     //0  => No Parity,  1 => Parity Enabled
#define  UARTMPARTYP        (1U << 3)     //0  => Odd parity, 1 => Even Parity

GPCFG_UARTS_TXDATA      = str(hex(int(GPCFG_BASE, 16) + int("0090", 16)))
GPCFG_UARTS_TXDATA      = GPCFG_UARTS_TXDATA[2:]
GPCFG_UARTS_RXDATA      = str(hex(int(GPCFG_BASE, 16) + int("0094", 16)))
GPCFG_UARTS_RXDATA      = GPCFG_UARTS_RXDATA[2:]
GPCFG_UARTS_TXSEND      = str(hex(int(GPCFG_BASE, 16) + int("0098", 16)))
GPCFG_UARTS_TXSEND      = GPCFG_UARTS_TXSEND[2:]

GPCFG_SPARE0            = str(hex(int(GPCFG_BASE, 16) + int("009c", 16)))
GPCFG_SPARE0            = GPCFG_SPARE0[2:]
GPCFG_SPARE1            = str(hex(int(GPCFG_BASE, 16) + int("00a0", 16)))
GPCFG_SPARE1            = GPCFG_SPARE1[2:]
GPCFG_SPARE2            = str(hex(int(GPCFG_BASE, 16) + int("00a4", 16)))
GPCFG_SPARE2            = GPCFG_SPARE2[2:]
GPCFG_FHECTL2          = str(hex(int(GPCFG_BASE, 16) + int("00a8", 16)))
GPCFG_FHECTL2          = GPCFG_FHECTL2[2:]

GPCFG_FHECTL3          = str(hex(int(GPCFG_BASE, 16) + int("800C", 16)))
GPCFG_FHECTL3          = GPCFG_FHECTL3[2:]
GPCFG_PADTESTOUT       = str(hex(int(GPCFG_BASE, 16) + int("8010", 16)))
GPCFG_PADTESTOUT       = GPCFG_PADTESTOUT[2:]
GPCFG_PADTESTIN        = str(hex(int(GPCFG_BASE, 16) + int("8014", 16)))
GPCFG_PADTESTIN        = GPCFG_PADTESTIN[2:]
GPCFG_COMMNDFIFO       = str(hex(int(GPCFG_BASE, 16) + int("8018", 16)))
GPCFG_COMMNDFIFO       = GPCFG_COMMNDFIFO[2:]

#//parameter CLEQCTL2_LOG2OFN       = 12'hFFF << 0;

GPCFG_SIGNATURE         = str(hex(int(GPCFG_BASE, 16) + int("00cc", 16)))
GPCFG_SIGNATURE         = GPCFG_SIGNATURE[2:]

GPCFG_FHECTLP_ADDR      = str(hex(int(GPCFG_BASE, 16) + int("8000", 16)))
GPCFG_FHECTLP_ADDR      = GPCFG_FHECTLP_ADDR[2:]
#define  CLCTLP_ENMODMUL       (1U << 0)
#define  CLCTLP_ENMODEXP       (1U << 1)
#define  CLCTLP_ENEXTGCD       (1U << 2)
#define  CLCTLP_ENGFUNC        (1U << 3)
#define  CLCTLP_ENHWRNG        (1U << 4)
#define  CLCTLP_FHERHIRQ        (1U << 8)


GPCFG_FHECTL_ADDR       = str(hex(int(GPCFG_BASE, 16) + int("8004", 16)))
GPCFG_FHECTL_ADDR       = GPCFG_FHECTL_ADDR[2:]

GPCFG_FHESTATUS_ADDR   = str(hex(int(GPCFG_BASE, 16) + int("8008", 16)))
GPCFG_FHESTATUS_ADDR   = GPCFG_FHESTATUS_ADDR[2:]

GPCFG_N_ADDR          = [str(hex(int(GPCFG_BASE, 16) + int("9000", 16))), str(hex(int(GPCFG_BASE, 16) + int("9004", 16))), str(hex(int(GPCFG_BASE, 16) + int("9008", 16))), str(hex(int(GPCFG_BASE, 16) + int("900C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9010", 16))), str(hex(int(GPCFG_BASE, 16) + int("9014", 16))), str(hex(int(GPCFG_BASE, 16) + int("9018", 16))), str(hex(int(GPCFG_BASE, 16) + int("901C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9020", 16))), str(hex(int(GPCFG_BASE, 16) + int("9024", 16))), str(hex(int(GPCFG_BASE, 16) + int("9028", 16))), str(hex(int(GPCFG_BASE, 16) + int("902C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9030", 16))), str(hex(int(GPCFG_BASE, 16) + int("9034", 16))), str(hex(int(GPCFG_BASE, 16) + int("9038", 16))), str(hex(int(GPCFG_BASE, 16) + int("903C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9040", 16))), str(hex(int(GPCFG_BASE, 16) + int("9044", 16))), str(hex(int(GPCFG_BASE, 16) + int("9048", 16))), str(hex(int(GPCFG_BASE, 16) + int("904C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9050", 16))), str(hex(int(GPCFG_BASE, 16) + int("9054", 16))), str(hex(int(GPCFG_BASE, 16) + int("9058", 16))), str(hex(int(GPCFG_BASE, 16) + int("905C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9060", 16))), str(hex(int(GPCFG_BASE, 16) + int("9064", 16))), str(hex(int(GPCFG_BASE, 16) + int("9068", 16))), str(hex(int(GPCFG_BASE, 16) + int("906C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9070", 16))), str(hex(int(GPCFG_BASE, 16) + int("9074", 16))), str(hex(int(GPCFG_BASE, 16) + int("9078", 16))), str(hex(int(GPCFG_BASE, 16) + int("907C", 16)))]
GPCFG_N_ADDR          = [GPCFG_N_ADDR[0][2:], GPCFG_N_ADDR[1][2:], GPCFG_N_ADDR[2][2:], GPCFG_N_ADDR[3][2:], GPCFG_N_ADDR[4][2:], GPCFG_N_ADDR[5][2:], GPCFG_N_ADDR[6][2:], GPCFG_N_ADDR[7][2:], GPCFG_N_ADDR[8][2:], GPCFG_N_ADDR[9][2:], GPCFG_N_ADDR[10][2:], GPCFG_N_ADDR[11][2:], GPCFG_N_ADDR[12][2:], GPCFG_N_ADDR[13][2:], GPCFG_N_ADDR[14][2:], GPCFG_N_ADDR[15][2:], GPCFG_N_ADDR[16][2:], GPCFG_N_ADDR[17][2:], GPCFG_N_ADDR[18][2:], GPCFG_N_ADDR[19][2:], GPCFG_N_ADDR[20][2:], GPCFG_N_ADDR[21][2:], GPCFG_N_ADDR[22][2:], GPCFG_N_ADDR[23][2:], GPCFG_N_ADDR[24][2:], GPCFG_N_ADDR[25][2:], GPCFG_N_ADDR[26][2:], GPCFG_N_ADDR[27][2:], GPCFG_N_ADDR[28][2:], GPCFG_N_ADDR[29][2:], GPCFG_N_ADDR[30][2:], GPCFG_N_ADDR[31][2:]]

GPCFG_NSQ_ADDR        = [str(hex(int(GPCFG_BASE, 16) + int("9100", 16))), str(hex(int(GPCFG_BASE, 16) + int("9104", 16))), str(hex(int(GPCFG_BASE, 16) + int("9108", 16))), str(hex(int(GPCFG_BASE, 16) + int("910C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9110", 16))), str(hex(int(GPCFG_BASE, 16) + int("9114", 16))), str(hex(int(GPCFG_BASE, 16) + int("9118", 16))), str(hex(int(GPCFG_BASE, 16) + int("911C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9120", 16))), str(hex(int(GPCFG_BASE, 16) + int("9124", 16))), str(hex(int(GPCFG_BASE, 16) + int("9128", 16))), str(hex(int(GPCFG_BASE, 16) + int("912C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9130", 16))), str(hex(int(GPCFG_BASE, 16) + int("9134", 16))), str(hex(int(GPCFG_BASE, 16) + int("9138", 16))), str(hex(int(GPCFG_BASE, 16) + int("913C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9140", 16))), str(hex(int(GPCFG_BASE, 16) + int("9144", 16))), str(hex(int(GPCFG_BASE, 16) + int("9148", 16))), str(hex(int(GPCFG_BASE, 16) + int("914C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9150", 16))), str(hex(int(GPCFG_BASE, 16) + int("9154", 16))), str(hex(int(GPCFG_BASE, 16) + int("9158", 16))), str(hex(int(GPCFG_BASE, 16) + int("915C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9160", 16))), str(hex(int(GPCFG_BASE, 16) + int("9164", 16))), str(hex(int(GPCFG_BASE, 16) + int("9168", 16))), str(hex(int(GPCFG_BASE, 16) + int("916C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9170", 16))), str(hex(int(GPCFG_BASE, 16) + int("9174", 16))), str(hex(int(GPCFG_BASE, 16) + int("9178", 16))), str(hex(int(GPCFG_BASE, 16) + int("917C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9180", 16))), str(hex(int(GPCFG_BASE, 16) + int("9184", 16))), str(hex(int(GPCFG_BASE, 16) + int("9188", 16))), str(hex(int(GPCFG_BASE, 16) + int("918C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9190", 16))), str(hex(int(GPCFG_BASE, 16) + int("9194", 16))), str(hex(int(GPCFG_BASE, 16) + int("9198", 16))), str(hex(int(GPCFG_BASE, 16) + int("919C", 16))), str(hex(int(GPCFG_BASE, 16) + int("91A0", 16))), str(hex(int(GPCFG_BASE, 16) + int("91A4", 16))), str(hex(int(GPCFG_BASE, 16) + int("91A8", 16))), str(hex(int(GPCFG_BASE, 16) + int("91AC", 16))), str(hex(int(GPCFG_BASE, 16) + int("91B0", 16))), str(hex(int(GPCFG_BASE, 16) + int("91B4", 16))), str(hex(int(GPCFG_BASE, 16) + int("91B8", 16))), str(hex(int(GPCFG_BASE, 16) + int("91BC", 16))), str(hex(int(GPCFG_BASE, 16) + int("91C0", 16))), str(hex(int(GPCFG_BASE, 16) + int("91C4", 16))), str(hex(int(GPCFG_BASE, 16) + int("91C8", 16))), str(hex(int(GPCFG_BASE, 16) + int("91CC", 16))), str(hex(int(GPCFG_BASE, 16) + int("91D0", 16))), str(hex(int(GPCFG_BASE, 16) + int("91D4", 16))), str(hex(int(GPCFG_BASE, 16) + int("91D8", 16))), str(hex(int(GPCFG_BASE, 16) + int("91DC", 16))), str(hex(int(GPCFG_BASE, 16) + int("91E0", 16))), str(hex(int(GPCFG_BASE, 16) + int("91E4", 16))), str(hex(int(GPCFG_BASE, 16) + int("91E8", 16))), str(hex(int(GPCFG_BASE, 16) + int("91EC", 16))), str(hex(int(GPCFG_BASE, 16) + int("91F0", 16))), str(hex(int(GPCFG_BASE, 16) + int("91F4", 16))), str(hex(int(GPCFG_BASE, 16) + int("91F8", 16))), str(hex(int(GPCFG_BASE, 16) + int("91FC", 16)))]
GPCFG_NSQ_ADDR        = [GPCFG_NSQ_ADDR[0][2:], GPCFG_NSQ_ADDR[1][2:], GPCFG_NSQ_ADDR[2][2:], GPCFG_NSQ_ADDR[3][2:], GPCFG_NSQ_ADDR[4][2:], GPCFG_NSQ_ADDR[5][2:], GPCFG_NSQ_ADDR[6][2:], GPCFG_NSQ_ADDR[7][2:], GPCFG_NSQ_ADDR[8][2:], GPCFG_NSQ_ADDR[9][2:], GPCFG_NSQ_ADDR[10][2:], GPCFG_NSQ_ADDR[11][2:], GPCFG_NSQ_ADDR[12][2:], GPCFG_NSQ_ADDR[13][2:], GPCFG_NSQ_ADDR[14][2:], GPCFG_NSQ_ADDR[15][2:], GPCFG_NSQ_ADDR[16][2:], GPCFG_NSQ_ADDR[17][2:], GPCFG_NSQ_ADDR[18][2:], GPCFG_NSQ_ADDR[19][2:], GPCFG_NSQ_ADDR[20][2:], GPCFG_NSQ_ADDR[21][2:], GPCFG_NSQ_ADDR[22][2:], GPCFG_NSQ_ADDR[23][2:], GPCFG_NSQ_ADDR[24][2:], GPCFG_NSQ_ADDR[25][2:], GPCFG_NSQ_ADDR[26][2:], GPCFG_NSQ_ADDR[27][2:], GPCFG_NSQ_ADDR[28][2:], GPCFG_NSQ_ADDR[29][2:], GPCFG_NSQ_ADDR[30][2:], GPCFG_NSQ_ADDR[31][2:], GPCFG_NSQ_ADDR[32][2:], GPCFG_NSQ_ADDR[33][2:], GPCFG_NSQ_ADDR[34][2:], GPCFG_NSQ_ADDR[35][2:], GPCFG_NSQ_ADDR[36][2:], GPCFG_NSQ_ADDR[37][2:], GPCFG_NSQ_ADDR[38][2:], GPCFG_NSQ_ADDR[39][2:], GPCFG_NSQ_ADDR[40][2:], GPCFG_NSQ_ADDR[41][2:], GPCFG_NSQ_ADDR[42][2:], GPCFG_NSQ_ADDR[43][2:], GPCFG_NSQ_ADDR[44][2:], GPCFG_NSQ_ADDR[45][2:], GPCFG_NSQ_ADDR[46][2:], GPCFG_NSQ_ADDR[47][2:], GPCFG_NSQ_ADDR[48][2:], GPCFG_NSQ_ADDR[49][2:], GPCFG_NSQ_ADDR[50][2:], GPCFG_NSQ_ADDR[51][2:], GPCFG_NSQ_ADDR[52][2:], GPCFG_NSQ_ADDR[53][2:], GPCFG_NSQ_ADDR[54][2:], GPCFG_NSQ_ADDR[55][2:], GPCFG_NSQ_ADDR[56][2:], GPCFG_NSQ_ADDR[57][2:], GPCFG_NSQ_ADDR[58][2:], GPCFG_NSQ_ADDR[59][2:], GPCFG_NSQ_ADDR[60][2:], GPCFG_NSQ_ADDR[61][2:], GPCFG_NSQ_ADDR[62][2:], GPCFG_NSQ_ADDR[63][2:]]

GPCFG_NINV_ADDR          = [str(hex(int(GPCFG_BASE, 16) + int("9080", 16))), str(hex(int(GPCFG_BASE, 16) + int("9084", 16))), str(hex(int(GPCFG_BASE, 16) + int("9088", 16))), str(hex(int(GPCFG_BASE, 16) + int("908C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9090", 16))), str(hex(int(GPCFG_BASE, 16) + int("9094", 16))), str(hex(int(GPCFG_BASE, 16) + int("9098", 16))), str(hex(int(GPCFG_BASE, 16) + int("909C", 16))), str(hex(int(GPCFG_BASE, 16) + int("90A0", 16))), str(hex(int(GPCFG_BASE, 16) + int("90A4", 16))), str(hex(int(GPCFG_BASE, 16) + int("90A8", 16))), str(hex(int(GPCFG_BASE, 16) + int("90AC", 16))), str(hex(int(GPCFG_BASE, 16) + int("90B0", 16))), str(hex(int(GPCFG_BASE, 16) + int("90B4", 16))), str(hex(int(GPCFG_BASE, 16) + int("90B8", 16))), str(hex(int(GPCFG_BASE, 16) + int("90BC", 16))), str(hex(int(GPCFG_BASE, 16) + int("90C0", 16))), str(hex(int(GPCFG_BASE, 16) + int("90C4", 16))), str(hex(int(GPCFG_BASE, 16) + int("90C8", 16))), str(hex(int(GPCFG_BASE, 16) + int("90CC", 16))), str(hex(int(GPCFG_BASE, 16) + int("90D0", 16))), str(hex(int(GPCFG_BASE, 16) + int("90D4", 16))), str(hex(int(GPCFG_BASE, 16) + int("90D8", 16))), str(hex(int(GPCFG_BASE, 16) + int("90DC", 16))), str(hex(int(GPCFG_BASE, 16) + int("90E0", 16))), str(hex(int(GPCFG_BASE, 16) + int("90E4", 16))), str(hex(int(GPCFG_BASE, 16) + int("90E8", 16))), str(hex(int(GPCFG_BASE, 16) + int("90EC", 16))), str(hex(int(GPCFG_BASE, 16) + int("90F0", 16))), str(hex(int(GPCFG_BASE, 16) + int("90F4", 16))), str(hex(int(GPCFG_BASE, 16) + int("90F8", 16))), str(hex(int(GPCFG_BASE, 16) + int("90FC", 16)))]
GPCFG_NINV_ADDR          = [GPCFG_NINV_ADDR[0][2:], GPCFG_NINV_ADDR[1][2:], GPCFG_NINV_ADDR[2][2:], GPCFG_NINV_ADDR[3][2:], GPCFG_NINV_ADDR[4][2:], GPCFG_NINV_ADDR[5][2:], GPCFG_NINV_ADDR[6][2:], GPCFG_NINV_ADDR[7][2:], GPCFG_NINV_ADDR[8][2:], GPCFG_NINV_ADDR[9][2:], GPCFG_NINV_ADDR[10][2:], GPCFG_NINV_ADDR[11][2:], GPCFG_NINV_ADDR[12][2:], GPCFG_NINV_ADDR[13][2:], GPCFG_NINV_ADDR[14][2:], GPCFG_NINV_ADDR[15][2:], GPCFG_NINV_ADDR[16][2:], GPCFG_NINV_ADDR[17][2:], GPCFG_NINV_ADDR[18][2:], GPCFG_NINV_ADDR[19][2:], GPCFG_NINV_ADDR[20][2:], GPCFG_NINV_ADDR[21][2:], GPCFG_NINV_ADDR[22][2:], GPCFG_NINV_ADDR[23][2:], GPCFG_NINV_ADDR[24][2:], GPCFG_NINV_ADDR[25][2:], GPCFG_NINV_ADDR[26][2:], GPCFG_NINV_ADDR[27][2:], GPCFG_NINV_ADDR[28][2:], GPCFG_NINV_ADDR[29][2:], GPCFG_NINV_ADDR[30][2:], GPCFG_NINV_ADDR[31][2:]]


GPCFG_DBG_ADDR          = [str(hex(int(GPCFG_BASE, 16) + int("9B00", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B04", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B08", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B0C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B10", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B14", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B18", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B1C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B20", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B24", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B28", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B2C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B30", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B34", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B38", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B3C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B40", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B44", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B48", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B4C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B50", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B54", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B58", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B5C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B60", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B64", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B68", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B6C", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B70", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B74", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B78", 16))), str(hex(int(GPCFG_BASE, 16) + int("9B7C", 16)))]
GPCFG_DBG_ADDR          = [GPCFG_DBG_ADDR[0][2:], GPCFG_DBG_ADDR[1][2:], GPCFG_DBG_ADDR[2][2:], GPCFG_DBG_ADDR[3][2:], GPCFG_DBG_ADDR[4][2:], GPCFG_DBG_ADDR[5][2:], GPCFG_DBG_ADDR[6][2:], GPCFG_DBG_ADDR[7][2:], GPCFG_DBG_ADDR[8][2:], GPCFG_DBG_ADDR[9][2:], GPCFG_DBG_ADDR[10][2:], GPCFG_DBG_ADDR[11][2:], GPCFG_DBG_ADDR[12][2:], GPCFG_DBG_ADDR[13][2:], GPCFG_DBG_ADDR[14][2:], GPCFG_DBG_ADDR[15][2:], GPCFG_DBG_ADDR[16][2:], GPCFG_DBG_ADDR[17][2:], GPCFG_DBG_ADDR[18][2:], GPCFG_DBG_ADDR[19][2:], GPCFG_DBG_ADDR[20][2:], GPCFG_DBG_ADDR[21][2:], GPCFG_DBG_ADDR[22][2:], GPCFG_DBG_ADDR[23][2:], GPCFG_DBG_ADDR[24][2:], GPCFG_DBG_ADDR[25][2:], GPCFG_DBG_ADDR[26][2:], GPCFG_DBG_ADDR[27][2:], GPCFG_DBG_ADDR[28][2:], GPCFG_DBG_ADDR[29][2:], GPCFG_DBG_ADDR[30][2:], GPCFG_DBG_ADDR[31][2:]]

#define GPIO_GPIO0_CTL         (*(unit32_t *) (GPIO_BASE + 0x0000))
#define GPIO_GPIO0_OUT         (*(unit32_t *) (GPIO_BASE + 0x0004))
#define GPIO_GPIO0_IN          (*(unit32_t *) (GPIO_BASE + 0x0008))
#define GPIO_GPIO1_CTL         (*(unit32_t *) (GPIO_BASE + 0x000c))
#define GPIO_GPIO1_OUT         (*(unit32_t *) (GPIO_BASE + 0x0010))
#define GPIO_GPIO1_IN          (*(unit32_t *) (GPIO_BASE + 0x0014))
#define GPIO_GPIO2_CTL         (*(unit32_t *) (GPIO_BASE + 0x0018))
#define GPIO_GPIO2_OUT         (*(unit32_t *) (GPIO_BASE + 0x001c))
#define GPIO_GPIO2_IN          (*(unit32_t *) (GPIO_BASE + 0x0020))
#define GPIO_GPIO3_CTL         (*(unit32_t *) (GPIO_BASE + 0x0024))
#define GPIO_GPIO3_OUT         (*(unit32_t *) (GPIO_BASE + 0x0028))
#define GPIO_GPIO3_IN          (*(unit32_t *) (GPIO_BASE + 0x002c))


