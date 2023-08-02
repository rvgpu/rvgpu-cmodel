       0: 13 01 01 fb  	addi	sp, sp, -80
       4: 23 34 11 04  	sd	ra, 72(sp)
       8: 23 30 81 04  	sd	s0, 64(sp)
       c: 13 04 01 05  	addi	s0, sp, 80
      10: 23 34 a4 fe  	sd	a0, -24(s0)
      14: 23 30 b4 fe  	sd	a1, -32(s0)
      18: 03 35 84 fe  	ld	a0, -24(s0)
      1c: 23 34 a4 fc  	sd	a0, -56(s0)
      20: 03 35 84 fc  	ld	a0, -56(s0)
      24: 03 35 05 00  	ld	a0, 0(a0)
      28: 23 3c a4 fc  	sd	a0, -40(s0)
      2c: 03 35 84 fc  	ld	a0, -56(s0)
      30: 03 35 85 00  	ld	a0, 8(a0)
      34: 23 38 a4 fc  	sd	a0, -48(s0)
      38: 03 35 84 fd  	ld	a0, -40(s0)
      3c: 83 35 04 fe  	ld	a1, -32(s0)
      40: 93 95 25 00  	slli	a1, a1, 2
      44: 33 05 b5 00  	add	a0, a0, a1
      48: 03 25 05 00  	lw	a0, 0(a0)
      4c: 23 22 a4 fc  	sw	a0, -60(s0)
      50: 03 25 44 fc  	lw	a0, -60(s0)
      54: 23 20 a4 fc  	sw	a0, -64(s0)
      58: 23 2e 04 fa  	sw	zero, -68(s0)
      5c: 6f 00 40 00  	j	0x60 <vs_main+0x60>
      60: 03 25 c4 fb  	lw	a0, -68(s0)
      64: 83 35 04 fe  	ld	a1, -32(s0)
      68: 63 56 b5 02  	bge	a0, a1, 0x94 <vs_main+0x94>
      6c: 6f 00 40 00  	j	0x70 <vs_main+0x70>
      70: 03 25 c4 fb  	lw	a0, -68(s0)
      74: 83 25 04 fc  	lw	a1, -64(s0)
      78: 3b 85 a5 00  	addw	a0, a1, a0
      7c: 23 20 a4 fc  	sw	a0, -64(s0)
      80: 6f 00 40 00  	j	0x84 <vs_main+0x84>
      84: 03 25 c4 fb  	lw	a0, -68(s0)
      88: 1b 05 15 00  	addiw	a0, a0, 1
      8c: 23 2e a4 fa  	sw	a0, -68(s0)
      90: 6f f0 1f fd  	j	0x60 <vs_main+0x60>
      94: 03 25 04 fc  	lw	a0, -64(s0)
      98: 83 35 04 fd  	ld	a1, -48(s0)
      9c: 03 36 04 fe  	ld	a2, -32(s0)
      a0: 13 16 26 00  	slli	a2, a2, 2
      a4: b3 85 c5 00  	add	a1, a1, a2
      a8: 23 a0 a5 00  	sw	a0, 0(a1)
      ac: 13 05 00 00  	li	a0, 0
      b0: 83 30 81 04  	ld	ra, 72(sp)
      b4: 03 34 01 04  	ld	s0, 64(sp)
      b8: 13 01 01 05  	addi	sp, sp, 80
      bc: 67 80 00 00  	ret
