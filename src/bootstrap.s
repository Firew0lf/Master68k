.section .vectors

.dc.l stack_top | initial SSP
.dc.l _start    | initial PC
.dc.l _berr     | bus error
.dc.l 0x000000  | address error
.dc.l 0x000000  | illegal instruction
.dc.l 0x000000  | zero divide
.dc.l 0x000000  | CHK instruction
.dc.l 0x000000  | TRAPV instruction
.dc.l 0x000000  | privilege violation
.dc.l 0x000000  | trace
.dc.l 0x000000  | Line A <unavailable>
.dc.l 0x000000  | Line F <unavailable>
.dc.l 0x000000  | [reserved]
.dc.l 0x000000  | coprocessor protocol violation
.dc.l 0x000000  | format error
.dc.l 0x000000  | uninitialized interrupt
.skip 32        | [reserved]
.dc.l _rte      | spurious interrupt
.dc.l irq1      | IRQ level 1
.dc.l irq2      | IRQ level 2
.dc.l irq3      | IRQ level 3
.dc.l irq4      | IRQ level 4
.dc.l irq5      | IRQ level 5
.dc.l irq6      | IRQ level 6
.dc.l irq7      | IRQ level 7
.dc.l trap1     | trap level 1
.dc.l trap2     | trap level 2
.dc.l trap3     | trap level 3
.dc.l trap4     | trap level 4
.dc.l trap5     | trap level 5
.dc.l trap6     | trap level 6
.dc.l trap7     | trap level 7
.dc.l trap8     | trap level 8
.dc.l trap9     | trap level 9
.dc.l trapA     | trap level A
.dc.l trapB     | trap level B
.dc.l trapC     | trap level C
.dc.l trapD     | trap level D
.dc.l trapE     | trap level E
.dc.l trapF     | trap level F
.skip 32        | FPU
.skip 12        | MMU
.skip 20        | [reserved]

.section .text
.align 4

.align 4
.globl _start
_start:
	|andw #0xf8ff, %sr | enable all interrupts
	jmp kernel_main
	
_stop:
	jmp _stop

_berr:
	rte

_rte:
	rte

.section .stack
.align 16
stack_bottom:
.skip 16384 | 16k stack
stack_top:
