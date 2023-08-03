
test.o:	file format elf64-littleriscv

Disassembly of section .text:

0000000000000000 <fs_main>:
       0: 13 01 01 f1  	addi	sp, sp, -240
       4: 23 34 11 0e  	sd	ra, 232(sp)
       8: 23 30 81 0e  	sd	s0, 224(sp)
       c: 13 04 01 0f  	addi	s0, sp, 240
      10: 23 34 a4 fe  	sd	a0, -24(s0)
      14: 23 30 b4 fe  	sd	a1, -32(s0)
      18: 23 3c c4 fc  	sd	a2, -40(s0)
      1c: 23 38 d4 fc  	sd	a3, -48(s0)
      20: 03 35 84 fe  	ld	a0, -24(s0)
      24: 23 34 a4 fc  	sd	a0, -56(s0)
      28: 03 35 84 fc  	ld	a0, -56(s0)
      2c: 03 35 05 00  	ld	a0, 0(a0)
      30: 23 30 a4 fc  	sd	a0, -64(s0)
      34: 03 35 84 fc  	ld	a0, -56(s0)
      38: 03 35 85 00  	ld	a0, 8(a0)
      3c: 23 3c a4 fa  	sd	a0, -72(s0)
      40: 03 35 84 fc  	ld	a0, -56(s0)
      44: 03 35 05 01  	ld	a0, 16(a0)
      48: 23 38 a4 fa  	sd	a0, -80(s0)
      4c: 03 35 04 fe  	ld	a0, -32(s0)
      50: 23 26 a4 fa  	sw	a0, -84(s0)
      54: 03 65 44 fe  	lwu	a0, -28(s0)
      58: 23 24 a4 fa  	sw	a0, -88(s0)
      5c: 03 35 84 fd  	ld	a0, -40(s0)
      60: 23 22 a4 fa  	sw	a0, -92(s0)
      64: 03 65 c4 fd  	lwu	a0, -36(s0)
      68: 23 20 a4 fa  	sw	a0, -96(s0)
      6c: 03 35 04 fd  	ld	a0, -48(s0)
      70: 23 2e a4 f8  	sw	a0, -100(s0)
      74: 03 35 04 fc  	ld	a0, -64(s0)
      78: 83 25 44 fa  	lw	a1, -92(s0)
      7c: 1b 96 35 00  	slliw	a2, a1, 3
      80: 3b 06 b6 40  	subw	a2, a2, a1
      84: 13 16 06 02  	slli	a2, a2, 32
      88: 13 56 e6 01  	srli	a2, a2, 30
      8c: 33 05 c5 00  	add	a0, a0, a2
      90: 07 20 05 00  	flw	ft0, 0(a0)
      94: 27 2c 04 f8  	fsw	ft0, -104(s0)
      98: 03 35 04 fc  	ld	a0, -64(s0)
      9c: 83 25 44 fa  	lw	a1, -92(s0)
      a0: 1b 96 35 00  	slliw	a2, a1, 3
      a4: 3b 06 b6 40  	subw	a2, a2, a1
      a8: 1b 06 16 00  	addiw	a2, a2, 1
      ac: 13 16 06 02  	slli	a2, a2, 32
      b0: 13 56 e6 01  	srli	a2, a2, 30
      b4: 33 05 c5 00  	add	a0, a0, a2
      b8: 07 20 05 00  	flw	ft0, 0(a0)
      bc: 27 2a 04 f8  	fsw	ft0, -108(s0)
      c0: 03 35 04 fc  	ld	a0, -64(s0)
      c4: 83 25 04 fa  	lw	a1, -96(s0)
      c8: 1b 96 35 00  	slliw	a2, a1, 3
      cc: 3b 06 b6 40  	subw	a2, a2, a1
      d0: 13 16 06 02  	slli	a2, a2, 32
      d4: 13 56 e6 01  	srli	a2, a2, 30
      d8: 33 05 c5 00  	add	a0, a0, a2
      dc: 07 20 05 00  	flw	ft0, 0(a0)
      e0: 27 28 04 f8  	fsw	ft0, -112(s0)
      e4: 03 35 04 fc  	ld	a0, -64(s0)
      e8: 83 25 04 fa  	lw	a1, -96(s0)
      ec: 1b 96 35 00  	slliw	a2, a1, 3
      f0: 3b 06 b6 40  	subw	a2, a2, a1
      f4: 1b 06 16 00  	addiw	a2, a2, 1
      f8: 13 16 06 02  	slli	a2, a2, 32
      fc: 13 56 e6 01  	srli	a2, a2, 30
     100: 33 05 c5 00  	add	a0, a0, a2
     104: 07 20 05 00  	flw	ft0, 0(a0)
     108: 27 26 04 f8  	fsw	ft0, -116(s0)
     10c: 03 35 04 fc  	ld	a0, -64(s0)
     110: 83 25 c4 f9  	lw	a1, -100(s0)
     114: 1b 96 35 00  	slliw	a2, a1, 3
     118: 3b 06 b6 40  	subw	a2, a2, a1
     11c: 13 16 06 02  	slli	a2, a2, 32
     120: 13 56 e6 01  	srli	a2, a2, 30
     124: 33 05 c5 00  	add	a0, a0, a2
     128: 07 20 05 00  	flw	ft0, 0(a0)
     12c: 27 24 04 f8  	fsw	ft0, -120(s0)
     130: 03 35 04 fc  	ld	a0, -64(s0)
     134: 83 25 c4 f9  	lw	a1, -100(s0)
     138: 1b 96 35 00  	slliw	a2, a1, 3
     13c: 3b 06 b6 40  	subw	a2, a2, a1
     140: 1b 06 16 00  	addiw	a2, a2, 1
     144: 13 16 06 02  	slli	a2, a2, 32
     148: 13 56 e6 01  	srli	a2, a2, 30
     14c: 33 05 c5 00  	add	a0, a0, a2
     150: 07 20 05 00  	flw	ft0, 0(a0)
     154: 27 22 04 f8  	fsw	ft0, -124(s0)
     158: 03 35 84 fb  	ld	a0, -72(s0)
     15c: 83 25 44 fa  	lw	a1, -92(s0)
     160: 1b 96 35 00  	slliw	a2, a1, 3
     164: 3b 06 b6 40  	subw	a2, a2, a1
     168: 1b 06 46 00  	addiw	a2, a2, 4
     16c: 13 16 06 02  	slli	a2, a2, 32
     170: 13 56 e6 01  	srli	a2, a2, 30
     174: 33 05 c5 00  	add	a0, a0, a2
     178: 07 20 05 00  	flw	ft0, 0(a0)
     17c: 27 20 04 f8  	fsw	ft0, -128(s0)
     180: 03 35 84 fb  	ld	a0, -72(s0)
     184: 83 25 44 fa  	lw	a1, -92(s0)
     188: 1b 96 35 00  	slliw	a2, a1, 3
     18c: 3b 06 b6 40  	subw	a2, a2, a1
     190: 1b 06 56 00  	addiw	a2, a2, 5
     194: 13 16 06 02  	slli	a2, a2, 32
     198: 13 56 e6 01  	srli	a2, a2, 30
     19c: 33 05 c5 00  	add	a0, a0, a2
     1a0: 07 20 05 00  	flw	ft0, 0(a0)
     1a4: 27 2e 04 f6  	fsw	ft0, -132(s0)
     1a8: 03 35 84 fb  	ld	a0, -72(s0)
     1ac: 83 25 44 fa  	lw	a1, -92(s0)
     1b0: 1b 96 35 00  	slliw	a2, a1, 3
     1b4: 3b 06 b6 40  	subw	a2, a2, a1
     1b8: 1b 06 66 00  	addiw	a2, a2, 6
     1bc: 13 16 06 02  	slli	a2, a2, 32
     1c0: 13 56 e6 01  	srli	a2, a2, 30
     1c4: 33 05 c5 00  	add	a0, a0, a2
     1c8: 07 20 05 00  	flw	ft0, 0(a0)
     1cc: 27 2c 04 f6  	fsw	ft0, -136(s0)
     1d0: 03 35 84 fb  	ld	a0, -72(s0)
     1d4: 83 25 04 fa  	lw	a1, -96(s0)
     1d8: 1b 96 35 00  	slliw	a2, a1, 3
     1dc: 3b 06 b6 40  	subw	a2, a2, a1
     1e0: 1b 06 46 00  	addiw	a2, a2, 4
     1e4: 13 16 06 02  	slli	a2, a2, 32
     1e8: 13 56 e6 01  	srli	a2, a2, 30
     1ec: 33 05 c5 00  	add	a0, a0, a2
     1f0: 07 20 05 00  	flw	ft0, 0(a0)
     1f4: 27 2a 04 f6  	fsw	ft0, -140(s0)
     1f8: 03 35 84 fb  	ld	a0, -72(s0)
     1fc: 83 25 04 fa  	lw	a1, -96(s0)
     200: 1b 96 35 00  	slliw	a2, a1, 3
     204: 3b 06 b6 40  	subw	a2, a2, a1
     208: 1b 06 56 00  	addiw	a2, a2, 5
     20c: 13 16 06 02  	slli	a2, a2, 32
     210: 13 56 e6 01  	srli	a2, a2, 30
     214: 33 05 c5 00  	add	a0, a0, a2
     218: 07 20 05 00  	flw	ft0, 0(a0)
     21c: 27 28 04 f6  	fsw	ft0, -144(s0)
     220: 03 35 84 fb  	ld	a0, -72(s0)
     224: 83 25 04 fa  	lw	a1, -96(s0)
     228: 1b 96 35 00  	slliw	a2, a1, 3
     22c: 3b 06 b6 40  	subw	a2, a2, a1
     230: 1b 06 66 00  	addiw	a2, a2, 6
     234: 13 16 06 02  	slli	a2, a2, 32
     238: 13 56 e6 01  	srli	a2, a2, 30
     23c: 33 05 c5 00  	add	a0, a0, a2
     240: 07 20 05 00  	flw	ft0, 0(a0)
     244: 27 26 04 f6  	fsw	ft0, -148(s0)
     248: 03 35 84 fb  	ld	a0, -72(s0)
     24c: 83 25 c4 f9  	lw	a1, -100(s0)
     250: 1b 96 35 00  	slliw	a2, a1, 3
     254: 3b 06 b6 40  	subw	a2, a2, a1
     258: 1b 06 46 00  	addiw	a2, a2, 4
     25c: 13 16 06 02  	slli	a2, a2, 32
     260: 13 56 e6 01  	srli	a2, a2, 30
     264: 33 05 c5 00  	add	a0, a0, a2
     268: 07 20 05 00  	flw	ft0, 0(a0)
     26c: 27 24 04 f6  	fsw	ft0, -152(s0)
     270: 03 35 84 fb  	ld	a0, -72(s0)
     274: 83 25 c4 f9  	lw	a1, -100(s0)
     278: 1b 96 35 00  	slliw	a2, a1, 3
     27c: 3b 06 b6 40  	subw	a2, a2, a1
     280: 1b 06 56 00  	addiw	a2, a2, 5
     284: 13 16 06 02  	slli	a2, a2, 32
     288: 13 56 e6 01  	srli	a2, a2, 30
     28c: 33 05 c5 00  	add	a0, a0, a2
     290: 07 20 05 00  	flw	ft0, 0(a0)
     294: 27 22 04 f6  	fsw	ft0, -156(s0)
     298: 03 35 84 fb  	ld	a0, -72(s0)
     29c: 83 25 c4 f9  	lw	a1, -100(s0)
     2a0: 1b 96 35 00  	slliw	a2, a1, 3
     2a4: 3b 06 b6 40  	subw	a2, a2, a1
     2a8: 1b 06 66 00  	addiw	a2, a2, 6
     2ac: 13 16 06 02  	slli	a2, a2, 32
     2b0: 13 56 e6 01  	srli	a2, a2, 30
     2b4: 33 05 c5 00  	add	a0, a0, a2
     2b8: 07 20 05 00  	flw	ft0, 0(a0)
     2bc: 27 20 04 f6  	fsw	ft0, -160(s0)
     2c0: 07 20 84 f9  	flw	ft0, -104(s0)
     2c4: 87 20 c4 f8  	flw	ft1, -116(s0)
     2c8: 07 21 44 f9  	flw	ft2, -108(s0)
     2cc: 87 21 04 f9  	flw	ft3, -112(s0)
     2d0: 53 72 31 10  	fmul.s	ft4, ft2, ft3
     2d4: 47 72 10 20  	fmsub.s	ft4, ft0, ft1, ft4
     2d8: 87 22 44 f8  	flw	ft5, -124(s0)
     2dc: 07 23 84 f8  	flw	ft6, -120(s0)
     2e0: d3 f0 60 10  	fmul.s	ft1, ft1, ft6
     2e4: c7 f0 51 08  	fmsub.s	ft1, ft3, ft5, ft1
     2e8: d3 70 12 00  	fadd.s	ft1, ft4, ft1
     2ec: 53 f0 02 10  	fmul.s	ft0, ft5, ft0
     2f0: 47 70 23 00  	fmsub.s	ft0, ft6, ft2, ft0
     2f4: 53 f0 00 00  	fadd.s	ft0, ft1, ft0
     2f8: 27 2e 04 f4  	fsw	ft0, -164(s0)
     2fc: 07 20 c4 f8  	flw	ft0, -116(s0)
     300: 87 20 44 f8  	flw	ft1, -124(s0)
     304: 53 70 10 08  	fsub.s	ft0, ft0, ft1
     308: 87 20 c4 f5  	flw	ft1, -164(s0)
     30c: 53 70 10 18  	fdiv.s	ft0, ft0, ft1
     310: 27 2c 04 f4  	fsw	ft0, -168(s0)
     314: 07 20 84 f8  	flw	ft0, -120(s0)
     318: 87 20 04 f9  	flw	ft1, -112(s0)
     31c: 53 70 10 08  	fsub.s	ft0, ft0, ft1
     320: 87 20 c4 f5  	flw	ft1, -164(s0)
     324: 53 70 10 18  	fdiv.s	ft0, ft0, ft1
     328: 27 2a 04 f4  	fsw	ft0, -172(s0)
     32c: 07 20 04 f9  	flw	ft0, -112(s0)
     330: 87 20 44 f8  	flw	ft1, -124(s0)
     334: 07 21 c4 f8  	flw	ft2, -116(s0)
     338: 87 21 84 f8  	flw	ft3, -120(s0)
     33c: 53 71 31 10  	fmul.s	ft2, ft2, ft3
     340: 47 70 10 10  	fmsub.s	ft0, ft0, ft1, ft2
     344: 87 20 c4 f5  	flw	ft1, -164(s0)
     348: 53 70 10 18  	fdiv.s	ft0, ft0, ft1
     34c: 27 28 04 f4  	fsw	ft0, -176(s0)
     350: 07 20 44 f8  	flw	ft0, -124(s0)
     354: 87 20 44 f9  	flw	ft1, -108(s0)
     358: 53 70 10 08  	fsub.s	ft0, ft0, ft1
     35c: 87 20 c4 f5  	flw	ft1, -164(s0)
     360: 53 70 10 18  	fdiv.s	ft0, ft0, ft1
     364: 27 26 04 f4  	fsw	ft0, -180(s0)
     368: 07 20 84 f9  	flw	ft0, -104(s0)
     36c: 87 20 84 f8  	flw	ft1, -120(s0)
     370: 53 70 10 08  	fsub.s	ft0, ft0, ft1
     374: 87 20 c4 f5  	flw	ft1, -164(s0)
     378: 53 70 10 18  	fdiv.s	ft0, ft0, ft1
     37c: 27 24 04 f4  	fsw	ft0, -184(s0)
     380: 07 20 84 f8  	flw	ft0, -120(s0)
     384: 87 20 44 f9  	flw	ft1, -108(s0)
     388: 07 21 44 f8  	flw	ft2, -124(s0)
     38c: 87 21 84 f9  	flw	ft3, -104(s0)
     390: 53 71 31 10  	fmul.s	ft2, ft2, ft3
     394: 47 70 10 10  	fmsub.s	ft0, ft0, ft1, ft2
     398: 87 20 c4 f5  	flw	ft1, -164(s0)
     39c: 53 70 10 18  	fdiv.s	ft0, ft0, ft1
     3a0: 27 22 04 f4  	fsw	ft0, -188(s0)
     3a4: 07 20 44 f9  	flw	ft0, -108(s0)
     3a8: 87 20 c4 f8  	flw	ft1, -116(s0)
     3ac: 53 70 10 08  	fsub.s	ft0, ft0, ft1
     3b0: 87 20 c4 f5  	flw	ft1, -164(s0)
     3b4: 53 70 10 18  	fdiv.s	ft0, ft0, ft1
     3b8: 27 20 04 f4  	fsw	ft0, -192(s0)
     3bc: 07 20 04 f9  	flw	ft0, -112(s0)
     3c0: 87 20 84 f9  	flw	ft1, -104(s0)
     3c4: 53 70 10 08  	fsub.s	ft0, ft0, ft1
     3c8: 87 20 c4 f5  	flw	ft1, -164(s0)
     3cc: 53 70 10 18  	fdiv.s	ft0, ft0, ft1
     3d0: 27 2e 04 f2  	fsw	ft0, -196(s0)
     3d4: 07 20 84 f9  	flw	ft0, -104(s0)
     3d8: 87 20 c4 f8  	flw	ft1, -116(s0)
     3dc: 07 21 44 f9  	flw	ft2, -108(s0)
     3e0: 87 21 04 f9  	flw	ft3, -112(s0)
     3e4: 53 71 31 10  	fmul.s	ft2, ft2, ft3
     3e8: 47 70 10 10  	fmsub.s	ft0, ft0, ft1, ft2
     3ec: 87 20 c4 f5  	flw	ft1, -164(s0)
     3f0: 53 70 10 18  	fdiv.s	ft0, ft0, ft1
     3f4: 27 2c 04 f2  	fsw	ft0, -200(s0)
     3f8: 03 65 c4 fa  	lwu	a0, -84(s0)
     3fc: 53 70 15 d0  	fcvt.s.wu	ft0, a0
     400: 37 05 00 00  	lui	a0, 0
     404: 87 20 05 00  	flw	ft1, 0(a0)
     408: 53 70 10 00  	fadd.s	ft0, ft0, ft1
     40c: 27 2a 04 f2  	fsw	ft0, -204(s0)
     410: 03 65 84 fa  	lwu	a0, -88(s0)
     414: 53 70 15 d0  	fcvt.s.wu	ft0, a0
     418: 53 70 10 00  	fadd.s	ft0, ft0, ft1
     41c: 27 28 04 f2  	fsw	ft0, -208(s0)
     420: 07 20 84 f5  	flw	ft0, -168(s0)
     424: 87 20 44 f3  	flw	ft1, -204(s0)
     428: 07 21 44 f5  	flw	ft2, -172(s0)
     42c: 87 21 04 f3  	flw	ft3, -208(s0)
     430: 53 71 31 10  	fmul.s	ft2, ft2, ft3
     434: 43 70 10 10  	fmadd.s	ft0, ft0, ft1, ft2
     438: 87 20 04 f5  	flw	ft1, -176(s0)
     43c: 53 70 10 00  	fadd.s	ft0, ft0, ft1
     440: 27 26 04 f2  	fsw	ft0, -212(s0)
     444: 07 20 c4 f4  	flw	ft0, -180(s0)
     448: 87 20 44 f3  	flw	ft1, -204(s0)
     44c: 07 21 84 f4  	flw	ft2, -184(s0)
     450: 87 21 04 f3  	flw	ft3, -208(s0)
     454: 53 71 31 10  	fmul.s	ft2, ft2, ft3
     458: 43 70 10 10  	fmadd.s	ft0, ft0, ft1, ft2
     45c: 87 20 44 f4  	flw	ft1, -188(s0)
     460: 53 70 10 00  	fadd.s	ft0, ft0, ft1
     464: 27 24 04 f2  	fsw	ft0, -216(s0)
     468: 07 20 04 f4  	flw	ft0, -192(s0)
     46c: 87 20 44 f3  	flw	ft1, -204(s0)
     470: 07 21 c4 f3  	flw	ft2, -196(s0)
     474: 87 21 04 f3  	flw	ft3, -208(s0)
     478: 53 71 31 10  	fmul.s	ft2, ft2, ft3
     47c: 43 70 10 10  	fmadd.s	ft0, ft0, ft1, ft2
     480: 87 20 84 f3  	flw	ft1, -200(s0)
     484: 53 70 10 00  	fadd.s	ft0, ft0, ft1
     488: 27 22 04 f2  	fsw	ft0, -220(s0)
     48c: 07 20 c4 f2  	flw	ft0, -212(s0)
     490: d3 00 00 f0  	fmv.w.x	ft1, zero
     494: 53 85 00 a0  	fle.s	a0, ft1, ft0
     498: 63 0a 05 02  	beqz	a0, 0x4cc <fs_main+0x4cc>
     49c: 6f 00 40 00  	j	0x4a0 <fs_main+0x4a0>
     4a0: 07 20 84 f2  	flw	ft0, -216(s0)
     4a4: d3 00 00 f0  	fmv.w.x	ft1, zero
     4a8: 53 85 00 a0  	fle.s	a0, ft1, ft0
     4ac: 63 00 05 02  	beqz	a0, 0x4cc <fs_main+0x4cc>
     4b0: 6f 00 40 00  	j	0x4b4 <fs_main+0x4b4>
     4b4: 07 20 44 f2  	flw	ft0, -220(s0)
     4b8: d3 00 00 f0  	fmv.w.x	ft1, zero
     4bc: d3 85 00 a0  	fle.s	a1, ft1, ft0
     4c0: 13 05 10 00  	li	a0, 1
     4c4: 63 96 05 04  	bnez	a1, 0x510 <fs_main+0x510>
     4c8: 6f 00 40 00  	j	0x4cc <fs_main+0x4cc>
     4cc: 07 20 c4 f2  	flw	ft0, -212(s0)
     4d0: d3 00 00 f0  	fmv.w.x	ft1, zero
     4d4: d3 05 10 a0  	fle.s	a1, ft0, ft1
     4d8: 13 05 00 00  	li	a0, 0
     4dc: 63 88 05 02  	beqz	a1, 0x50c <fs_main+0x50c>
     4e0: 6f 00 40 00  	j	0x4e4 <fs_main+0x4e4>
     4e4: 07 20 84 f2  	flw	ft0, -216(s0)
     4e8: d3 00 00 f0  	fmv.w.x	ft1, zero
     4ec: d3 05 10 a0  	fle.s	a1, ft0, ft1
     4f0: 13 05 00 00  	li	a0, 0
     4f4: 63 8c 05 00  	beqz	a1, 0x50c <fs_main+0x50c>
     4f8: 6f 00 40 00  	j	0x4fc <fs_main+0x4fc>
     4fc: 07 20 44 f2  	flw	ft0, -220(s0)
     500: d3 00 00 f0  	fmv.w.x	ft1, zero
     504: 53 05 10 a0  	fle.s	a0, ft0, ft1
     508: 6f 00 40 00  	j	0x50c <fs_main+0x50c>
     50c: 6f 00 40 00  	j	0x510 <fs_main+0x510>
     510: 13 75 15 00  	andi	a0, a0, 1
     514: 23 20 a4 f2  	sw	a0, -224(s0)
     518: 03 25 04 f2  	lw	a0, -224(s0)
     51c: 63 00 05 16  	beqz	a0, 0x67c <fs_main+0x67c>
     520: 6f 00 40 00  	j	0x524 <fs_main+0x524>
     524: 07 20 c4 f2  	flw	ft0, -212(s0)
     528: 87 20 04 f8  	flw	ft1, -128(s0)
     52c: 07 21 84 f2  	flw	ft2, -216(s0)
     530: 87 21 44 f7  	flw	ft3, -140(s0)
     534: 53 71 31 10  	fmul.s	ft2, ft2, ft3
     538: 43 70 10 10  	fmadd.s	ft0, ft0, ft1, ft2
     53c: 87 20 44 f2  	flw	ft1, -220(s0)
     540: 07 21 84 f6  	flw	ft2, -152(s0)
     544: 43 f0 20 00  	fmadd.s	ft0, ft1, ft2, ft0
     548: 27 2e 04 f0  	fsw	ft0, -228(s0)
     54c: 07 20 c4 f2  	flw	ft0, -212(s0)
     550: 87 20 c4 f7  	flw	ft1, -132(s0)
     554: 07 21 84 f2  	flw	ft2, -216(s0)
     558: 87 21 04 f7  	flw	ft3, -144(s0)
     55c: 53 71 31 10  	fmul.s	ft2, ft2, ft3
     560: 43 70 10 10  	fmadd.s	ft0, ft0, ft1, ft2
     564: 87 20 44 f2  	flw	ft1, -220(s0)
     568: 07 21 44 f6  	flw	ft2, -156(s0)
     56c: 43 f0 20 00  	fmadd.s	ft0, ft1, ft2, ft0
     570: 27 2c 04 f0  	fsw	ft0, -232(s0)
     574: 07 20 c4 f2  	flw	ft0, -212(s0)
     578: 87 20 84 f7  	flw	ft1, -136(s0)
     57c: 07 21 84 f2  	flw	ft2, -216(s0)
     580: 87 21 c4 f6  	flw	ft3, -148(s0)
     584: 53 71 31 10  	fmul.s	ft2, ft2, ft3
     588: 43 70 10 10  	fmadd.s	ft0, ft0, ft1, ft2
     58c: 87 20 44 f2  	flw	ft1, -220(s0)
     590: 07 21 04 f6  	flw	ft2, -160(s0)
     594: 43 f0 20 00  	fmadd.s	ft0, ft1, ft2, ft0
     598: 27 2a 04 f0  	fsw	ft0, -236(s0)
     59c: 07 20 c4 f1  	flw	ft0, -228(s0)
     5a0: 37 05 00 00  	lui	a0, 0
     5a4: 87 20 05 00  	flw	ft1, 0(a0)
     5a8: 53 70 10 10  	fmul.s	ft0, ft0, ft1
     5ac: 53 15 30 c0  	fcvt.lu.s	a0, ft0, rtz
     5b0: 83 35 04 fb  	ld	a1, -80(s0)
     5b4: 03 26 84 fa  	lw	a2, -88(s0)
     5b8: 93 06 00 32  	li	a3, 800
     5bc: 3b 06 d6 02  	mulw	a2, a2, a3
     5c0: 03 27 c4 fa  	lw	a4, -84(s0)
     5c4: 3b 06 e6 00  	addw	a2, a2, a4
     5c8: 13 16 26 02  	slli	a2, a2, 34
     5cc: 13 56 06 02  	srli	a2, a2, 32
     5d0: b3 85 c5 00  	add	a1, a1, a2
     5d4: 23 80 a5 00  	sb	a0, 0(a1)
     5d8: 07 20 84 f1  	flw	ft0, -232(s0)
     5dc: 53 70 10 10  	fmul.s	ft0, ft0, ft1
     5e0: 53 15 30 c0  	fcvt.lu.s	a0, ft0, rtz
     5e4: 83 35 04 fb  	ld	a1, -80(s0)
     5e8: 03 26 84 fa  	lw	a2, -88(s0)
     5ec: 33 06 d6 02  	mul	a2, a2, a3
     5f0: 03 27 c4 fa  	lw	a4, -84(s0)
     5f4: 33 06 e6 00  	add	a2, a2, a4
     5f8: 13 16 26 00  	slli	a2, a2, 2
     5fc: 13 06 16 00  	addi	a2, a2, 1
     600: 13 16 06 02  	slli	a2, a2, 32
     604: 13 56 06 02  	srli	a2, a2, 32
     608: b3 85 c5 00  	add	a1, a1, a2
     60c: 23 80 a5 00  	sb	a0, 0(a1)
     610: 07 20 44 f1  	flw	ft0, -236(s0)
     614: 53 70 10 10  	fmul.s	ft0, ft0, ft1
     618: 53 15 30 c0  	fcvt.lu.s	a0, ft0, rtz
     61c: 83 35 04 fb  	ld	a1, -80(s0)
     620: 03 26 84 fa  	lw	a2, -88(s0)
     624: 33 06 d6 02  	mul	a2, a2, a3
     628: 03 27 c4 fa  	lw	a4, -84(s0)
     62c: 33 06 e6 00  	add	a2, a2, a4
     630: 13 16 26 00  	slli	a2, a2, 2
     634: 13 06 26 00  	addi	a2, a2, 2
     638: 13 16 06 02  	slli	a2, a2, 32
     63c: 13 56 06 02  	srli	a2, a2, 32
     640: b3 85 c5 00  	add	a1, a1, a2
     644: 23 80 a5 00  	sb	a0, 0(a1)
     648: 03 35 04 fb  	ld	a0, -80(s0)
     64c: 83 25 84 fa  	lw	a1, -88(s0)
     650: b3 85 d5 02  	mul	a1, a1, a3
     654: 03 26 c4 fa  	lw	a2, -84(s0)
     658: b3 85 c5 00  	add	a1, a1, a2
     65c: 93 95 25 00  	slli	a1, a1, 2
     660: 93 85 35 00  	addi	a1, a1, 3
     664: 93 95 05 02  	slli	a1, a1, 32
     668: 93 d5 05 02  	srli	a1, a1, 32
     66c: 33 05 b5 00  	add	a0, a0, a1
     670: 93 05 f0 0f  	li	a1, 255
     674: 23 00 b5 00  	sb	a1, 0(a0)
     678: 6f 00 80 00  	j	0x680 <fs_main+0x680>
     67c: 6f 00 40 00  	j	0x680 <fs_main+0x680>
     680: 13 05 00 00  	li	a0, 0
     684: 83 30 81 0e  	ld	ra, 232(sp)
     688: 03 34 01 0e  	ld	s0, 224(sp)
     68c: 13 01 01 0f  	addi	sp, sp, 240
     690: 67 80 00 00  	ret
