
       0: 13 01 01 f6  	addi	sp, sp, -160
       4: 23 3c 11 08  	sd	ra, 152(sp)
       8: 23 38 81 08  	sd	s0, 144(sp)
       c: 13 04 01 0a  	addi	s0, sp, 160
      10: 23 34 a4 fe  	sd	a0, -24(s0)
      14: 23 30 b4 fe  	sd	a1, -32(s0)
      18: 03 35 84 fe  	ld	a0, -24(s0)
      1c: 23 3c a4 fc  	sd	a0, -40(s0)
      20: 03 35 84 fd  	ld	a0, -40(s0)
      24: 03 35 85 00  	ld	a0, 8(a0)
      28: 23 38 a4 fc  	sd	a0, -48(s0)
      2c: 03 35 84 fd  	ld	a0, -40(s0)
      30: 03 35 05 01  	ld	a0, 16(a0)
      34: 23 34 a4 fc  	sd	a0, -56(s0)
      38: 13 05 f0 fb  	li	a0, -65
      3c: 13 15 85 03  	slli	a0, a0, 56
      40: 23 30 a4 fc  	sd	a0, -64(s0)
      44: 13 05 f0 03  	li	a0, 63
      48: 13 15 05 02  	slli	a0, a0, 32
      4c: 93 05 f5 03  	addi	a1, a0, 63
      50: 93 95 85 01  	slli	a1, a1, 24
      54: 23 3c b4 fa  	sd	a1, -72(s0)
      58: 13 05 f5 0b  	addi	a0, a0, 191
      5c: 13 15 85 01  	slli	a0, a0, 24
      60: 23 38 a4 fa  	sd	a0, -80(s0)
      64: 23 24 04 fa  	sw	zero, -88(s0)
      68: 23 30 04 fa  	sd	zero, -96(s0)
      6c: 23 3c 04 f8  	sd	zero, -104(s0)
      70: 23 38 04 f8  	sd	zero, -112(s0)
      74: 23 34 04 f8  	sd	zero, -120(s0)
      78: 37 05 80 3f  	lui	a0, 260096
      7c: 23 28 a4 f8  	sw	a0, -112(s0)
      80: 23 2c a4 f8  	sw	a0, -104(s0)
      84: 23 20 a4 fa  	sw	a0, -96(s0)
      88: 83 35 04 fe  	ld	a1, -32(s0)
      8c: 93 95 35 00  	slli	a1, a1, 3
      90: 13 06 04 fb  	addi	a2, s0, -80
      94: b3 05 b6 00  	add	a1, a2, a1
      98: 07 a0 05 00  	flw	ft0, 0(a1)
      9c: 27 22 04 f8  	fsw	ft0, -124(s0)
      a0: 83 35 04 fe  	ld	a1, -32(s0)
      a4: 93 95 35 00  	slli	a1, a1, 3
      a8: b3 05 b6 00  	add	a1, a2, a1
      ac: 07 a0 45 00  	flw	ft0, 4(a1)
      b0: 27 20 04 f8  	fsw	ft0, -128(s0)
      b4: 23 2e 04 f6  	sw	zero, -132(s0)
      b8: 23 2c a4 f6  	sw	a0, -136(s0)
      bc: 03 35 04 fe  	ld	a0, -32(s0)
      c0: 93 05 c0 00  	li	a1, 12
      c4: 33 05 b5 02  	mul	a0, a0, a1
      c8: 13 06 84 f8  	addi	a2, s0, -120
      cc: 33 05 a6 00  	add	a0, a2, a0
      d0: 07 20 05 00  	flw	ft0, 0(a0)
      d4: 27 2a 04 f6  	fsw	ft0, -140(s0)
      d8: 03 35 04 fe  	ld	a0, -32(s0)
      dc: 33 05 b5 02  	mul	a0, a0, a1
      e0: 33 05 a6 00  	add	a0, a2, a0
      e4: 07 20 45 00  	flw	ft0, 4(a0)
      e8: 27 28 04 f6  	fsw	ft0, -144(s0)
      ec: 03 35 04 fe  	ld	a0, -32(s0)
      f0: 33 05 b5 02  	mul	a0, a0, a1
      f4: 33 05 a6 00  	add	a0, a2, a0
      f8: 07 20 85 00  	flw	ft0, 8(a0)
      fc: 27 26 04 f6  	fsw	ft0, -148(s0)
     100: 03 35 84 fd  	ld	a0, -40(s0)
     104: 03 35 05 00  	ld	a0, 0(a0)
     108: 23 30 a4 f6  	sd	a0, -160(s0)
     10c: 03 35 04 f6  	ld	a0, -160(s0)
     110: 07 20 85 00  	flw	ft0, 8(a0)
     114: 87 20 44 f8  	flw	ft1, -124(s0)
     118: 43 f0 00 00  	fmadd.s	ft0, ft1, ft0, ft0
     11c: 27 22 04 f8  	fsw	ft0, -124(s0)
     120: 03 35 04 f6  	ld	a0, -160(s0)
     124: 07 20 c5 00  	flw	ft0, 12(a0)
     128: 87 20 04 f8  	flw	ft1, -128(s0)
     12c: 43 f0 00 00  	fmadd.s	ft0, ft1, ft0, ft0
     130: 27 20 04 f8  	fsw	ft0, -128(s0)
     134: 07 20 44 f8  	flw	ft0, -124(s0)
     138: 03 35 04 fd  	ld	a0, -48(s0)
     13c: 83 35 04 fe  	ld	a1, -32(s0)
     140: 13 06 c0 01  	li	a2, 28
     144: b3 85 c5 02  	mul	a1, a1, a2
     148: 33 05 b5 00  	add	a0, a0, a1
     14c: 27 20 05 00  	fsw	ft0, 0(a0)
     150: 07 20 04 f8  	flw	ft0, -128(s0)
     154: 03 35 04 fd  	ld	a0, -48(s0)
     158: 83 35 04 fe  	ld	a1, -32(s0)
     15c: b3 85 c5 02  	mul	a1, a1, a2
     160: 33 85 a5 00  	add	a0, a1, a0
     164: 27 22 05 00  	fsw	ft0, 4(a0)
     168: 07 20 c4 f7  	flw	ft0, -132(s0)
     16c: 03 35 04 fd  	ld	a0, -48(s0)
     170: 83 35 04 fe  	ld	a1, -32(s0)
     174: b3 85 c5 02  	mul	a1, a1, a2
     178: 33 85 a5 00  	add	a0, a1, a0
     17c: 27 24 05 00  	fsw	ft0, 8(a0)
     180: 07 20 84 f7  	flw	ft0, -136(s0)
     184: 03 35 04 fd  	ld	a0, -48(s0)
     188: 83 35 04 fe  	ld	a1, -32(s0)
     18c: b3 85 c5 02  	mul	a1, a1, a2
     190: 33 85 a5 00  	add	a0, a1, a0
     194: 27 26 05 00  	fsw	ft0, 12(a0)
     198: 07 20 44 f7  	flw	ft0, -140(s0)
     19c: 03 35 84 fc  	ld	a0, -56(s0)
     1a0: 83 35 04 fe  	ld	a1, -32(s0)
     1a4: b3 85 c5 02  	mul	a1, a1, a2
     1a8: 33 85 a5 00  	add	a0, a1, a0
     1ac: 27 28 05 00  	fsw	ft0, 16(a0)
     1b0: 07 20 04 f7  	flw	ft0, -144(s0)
     1b4: 03 35 84 fc  	ld	a0, -56(s0)
     1b8: 83 35 04 fe  	ld	a1, -32(s0)
     1bc: b3 85 c5 02  	mul	a1, a1, a2
     1c0: 33 85 a5 00  	add	a0, a1, a0
     1c4: 27 2a 05 00  	fsw	ft0, 20(a0)
     1c8: 07 20 c4 f6  	flw	ft0, -148(s0)
     1cc: 03 35 84 fc  	ld	a0, -56(s0)
     1d0: 83 35 04 fe  	ld	a1, -32(s0)
     1d4: b3 85 c5 02  	mul	a1, a1, a2
     1d8: 33 85 a5 00  	add	a0, a1, a0
     1dc: 27 2c 05 00  	fsw	ft0, 24(a0)
     1e0: 13 05 00 00  	li	a0, 0
     1e4: 83 30 81 09  	ld	ra, 152(sp)
     1e8: 03 34 01 09  	ld	s0, 144(sp)
     1ec: 13 01 01 0a  	addi	sp, sp, 160
     1f0: 67 80 00 00  	ret
