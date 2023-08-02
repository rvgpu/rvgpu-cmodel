       0: 13 01 01 fb  	addi	sp, sp, -80
       4: 23 34 11 04  	sd	ra, 72(sp)
       8: 23 30 81 04  	sd	s0, 64(sp)
       c: 13 04 01 05  	addi	s0, sp, 80
      10: 23 34 a4 fe  	sd	a0, -24(s0)
      14: 23 30 b4 fe  	sd	a1, -32(s0)
      18: 23 3c c4 fc  	sd	a2, -40(s0)
      1c: 23 38 d4 fc  	sd	a3, -48(s0)
      20: 03 35 84 fe  	ld	a0, -24(s0)
      24: 23 34 a4 fc  	sd	a0, -56(s0)
      28: 03 35 04 fe  	ld	a0, -32(s0)
      2c: 23 22 a4 fc  	sw	a0, -60(s0)
      30: 03 65 44 fe  	lwu	a0, -28(s0)
      34: 23 20 a4 fc  	sw	a0, -64(s0)
      38: 03 35 84 fd  	ld	a0, -40(s0)
      3c: 23 2e a4 fa  	sw	a0, -68(s0)
      40: 03 65 c4 fd  	lwu	a0, -36(s0)
      44: 23 2c a4 fa  	sw	a0, -72(s0)
      48: 13 05 00 00  	li	a0, 0
      4c: 83 30 81 04  	ld	ra, 72(sp)
      50: 03 34 01 04  	ld	s0, 64(sp)
      54: 13 01 01 05  	addi	sp, sp, 80
      58: 67 80 00 00  	ret
