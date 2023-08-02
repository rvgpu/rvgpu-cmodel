       0: 13 01 01 fc  	addi	sp, sp, -64
       4: 23 3c 11 02  	sd	ra, 56(sp)
       8: 23 38 81 02  	sd	s0, 48(sp)
       c: 13 04 01 04  	addi	s0, sp, 64
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
      58: 03 35 04 fe  	ld	a0, -32(s0)
      5c: 93 55 f5 03  	srli	a1, a0, 63
      60: b3 05 b5 00  	add	a1, a0, a1
      64: 93 f5 e5 ff  	andi	a1, a1, -2
      68: 33 05 b5 40  	sub	a0, a0, a1
      6c: 63 16 05 04  	bnez	a0, 0xb8 <vs_main+0xb8>
      70: 6f 00 40 00  	j	0x74 <vs_main+0x74>
      74: 03 35 04 fe  	ld	a0, -32(s0)
      78: 93 55 f5 43  	srai	a1, a0, 63
      7c: 93 d5 e5 03  	srli	a1, a1, 62
      80: b3 05 b5 00  	add	a1, a0, a1
      84: 93 f5 c5 ff  	andi	a1, a1, -4
      88: 33 05 b5 40  	sub	a0, a0, a1
      8c: 63 1c 05 00  	bnez	a0, 0xa4 <vs_main+0xa4>
      90: 6f 00 40 00  	j	0x94 <vs_main+0x94>
      94: 03 25 04 fc  	lw	a0, -64(s0)
      98: 1b 05 05 19  	addiw	a0, a0, 400
      9c: 23 20 a4 fc  	sw	a0, -64(s0)
      a0: 6f 00 40 01  	j	0xb4 <vs_main+0xb4>
      a4: 03 25 04 fc  	lw	a0, -64(s0)
      a8: 1b 05 85 0c  	addiw	a0, a0, 200
      ac: 23 20 a4 fc  	sw	a0, -64(s0)
      b0: 6f 00 40 00  	j	0xb4 <vs_main+0xb4>
      b4: 6f 00 40 01  	j	0xc8 <vs_main+0xc8>
      b8: 03 25 04 fc  	lw	a0, -64(s0)
      bc: 1b 05 45 06  	addiw	a0, a0, 100
      c0: 23 20 a4 fc  	sw	a0, -64(s0)
      c4: 6f 00 40 00  	j	0xc8 <vs_main+0xc8>
      c8: 03 25 04 fc  	lw	a0, -64(s0)
      cc: 83 35 04 fd  	ld	a1, -48(s0)
      d0: 03 36 04 fe  	ld	a2, -32(s0)
      d4: 13 16 26 00  	slli	a2, a2, 2
      d8: b3 85 c5 00  	add	a1, a1, a2
      dc: 23 a0 a5 00  	sw	a0, 0(a1)
      e0: 13 05 00 00  	li	a0, 0
      e4: 83 30 81 03  	ld	ra, 56(sp)
      e8: 03 34 01 03  	ld	s0, 48(sp)
      ec: 13 01 01 04  	addi	sp, sp, 64
      f0: 67 80 00 00  	ret
