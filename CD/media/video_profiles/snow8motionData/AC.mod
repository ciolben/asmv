# Motion2D-1.3.11 Copyright (c) 1995-2005 by INRIA
# 
# This file contains the parameter values of the estimated 2D 
# parametric motion model. A comment line starts with the # 
# character. After the comments, the first line refers to the 
# estimated model id. The next line to a multiplier factor 
# applied to all the motion model parameters (c1,c2,a1...a4,q1..q6)
# to increase their resolution. Next, each line refers to the 
# motion model estimated between two successive images. 
# 
# The data signification is given below. 
# 
# |--------------------------------------------------------| 
# | column | data signification for each estimation        | 
# | number | between two successive images.                | 
# |--------|-----------------------------------------------| 
# |   1    | number of the first image                     | 
# |--------|-----------------------------------------------| 
# |   2    | motion model origin (row coordinate or yc)    | 
# |   3    | motion model origin (column coordinate or xc) | 
# |--------|-----------------------------------------------| 
# |   4    | motion model parameter (c1)                   | 
# |   5    | motion model parameter (c2)                   | 
# |--------|-----------------------------------------------| 
# |   6    | motion model parameter (a1)                   | 
# |   7    | motion model parameter (a2)                   | 
# |   8    | motion model parameter (a3)                   | 
# |   9    | motion model parameter (a4)                   | 
# |--------|-----------------------------------------------| 
# |  10    | motion model parameter (q1)                   | 
# |  11    | motion model parameter (q2)                   | 
# |  12    | motion model parameter (q3)                   | 
# |  13    | motion model parameter (q4)                   | 
# |  14    | motion model parameter (q5)                   | 
# |  15    | motion model parameter (q6)                   | 
# |--------|-----------------------------------------------| 
# |  16    | illumination variation parameter              | 
# |--------|-----------------------------------------------| 
# |  17    | support size (only if computed, by default)   | 
# |--------|-----------------------------------------------| 
#  
MODEL_ID = MDL_AFF_COMPLET
MULTIPLIER_FACTOR = 1.000000
0 135.000000 240.000000 2.320950 0.022418 0.000938 -0.000911 0.000561 0.001382 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.901681 
1 135.000000 240.000000 2.438334 0.127736 0.001113 -0.001077 -0.000737 0.001292 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.893491 
2 135.000000 240.000000 2.782834 0.262384 0.002047 -0.001172 -0.000919 0.002762 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.864718 
3 135.000000 240.000000 3.377546 0.491083 0.001257 -0.001694 -0.001847 0.001709 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.847585 
4 135.000000 240.000000 3.708279 0.410474 0.002410 -0.001717 -0.002033 0.003183 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.817428 
5 135.000000 240.000000 4.363642 0.440293 0.000126 -0.004826 -0.003677 -0.000435 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.812368 
6 135.000000 240.000000 4.902962 0.557924 0.001259 -0.003676 -0.001493 0.001100 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.789792 
7 135.000000 240.000000 4.887637 0.373373 0.001035 -0.006168 -0.000719 0.000488 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.795588 
8 135.000000 240.000000 4.634814 0.406067 0.001116 -0.006281 0.000596 -0.000255 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.793288 
9 135.000000 240.000000 4.811686 0.632314 0.000493 -0.007075 0.001430 0.000286 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.795727 
10 135.000000 240.000000 5.094054 0.850799 0.001933 -0.009040 -0.001000 -0.001568 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.787951 
11 135.000000 240.000000 5.816806 1.280950 0.000986 -0.008559 -0.000222 -0.002644 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.776279 
12 135.000000 240.000000 6.416637 1.842854 -0.000546 -0.009021 -0.001384 -0.003922 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.764964 
13 135.000000 240.000000 6.965202 2.423495 0.000102 -0.007396 -0.000535 -0.002449 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.751577 
14 135.000000 240.000000 7.088542 2.457961 0.000789 -0.006517 -0.002202 -0.001126 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.744597 
15 135.000000 240.000000 7.552890 2.376053 0.001271 -0.004861 -0.003818 -0.001769 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.749377 
16 135.000000 240.000000 7.794877 2.142593 0.002209 -0.004688 -0.005053 -0.003235 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.747235 
17 135.000000 240.000000 8.247260 2.012191 0.003206 -0.004714 -0.002956 -0.003379 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.741655 
18 135.000000 240.000000 8.677679 2.146844 0.005357 -0.002481 -0.006739 -0.001982 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.738762 
19 135.000000 240.000000 9.157730 2.211785 0.004238 0.000845 -0.008398 -0.000962 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.733161 
20 135.000000 240.000000 9.768868 2.036937 0.004557 0.000843 -0.008967 -0.001679 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.720946 
21 135.000000 240.000000 10.475508 2.279590 0.001888 0.001141 -0.008667 -0.001948 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.698067 
22 135.000000 240.000000 11.223979 2.248255 0.005232 -0.000270 -0.006401 0.000898 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.679602 
23 135.000000 240.000000 11.764429 2.121850 -0.001105 0.000565 -0.004265 0.001093 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.686732 
24 135.000000 240.000000 11.832023 1.615685 0.000326 0.002037 -0.002027 0.002286 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.695214 
25 135.000000 240.000000 11.561784 1.308378 -0.000038 0.002438 -0.006372 0.000727 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.692239 
26 135.000000 240.000000 11.501015 1.338216 0.001455 0.001609 -0.006053 0.003062 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.673875 
27 135.000000 240.000000 11.525861 1.122355 0.001137 0.002812 -0.003131 0.003499 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.670248 
28 135.000000 240.000000 11.842692 0.634044 -0.001175 -0.000046 -0.003216 0.003936 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.647211 
29 135.000000 240.000000 11.778478 0.332222 0.001861 0.001231 -0.005466 0.004649 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.615336 
30 135.000000 240.000000 12.302625 0.054410 0.001620 0.002529 -0.008895 0.003966 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.598152 
31 135.000000 240.000000 12.708201 0.028708 -0.000061 0.001769 -0.011727 -0.003320 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.571816 
32 135.000000 240.000000 12.717939 -0.294185 -0.001194 0.003518 -0.008035 -0.006903 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.564997 
33 135.000000 240.000000 11.951984 -1.375661 -0.002700 0.004483 -0.011206 -0.007507 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.590925 
34 135.000000 240.000000 11.534720 -2.441370 -0.004159 0.002278 -0.002997 -0.007340 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.593686 
35 135.000000 240.000000 11.373556 -2.692854 -0.005369 0.000607 -0.000109 -0.009512 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.592874 
36 135.000000 240.000000 11.237070 -3.211771 -0.001162 -0.000395 0.001826 -0.005473 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.600056 
37 135.000000 240.000000 10.254555 -3.937058 -0.001375 -0.001432 0.004462 -0.004070 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.622849 
38 135.000000 240.000000 9.507215 -5.050568 -0.003919 -0.000790 0.005649 -0.005585 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.631305 
39 135.000000 240.000000 8.969879 -5.211134 -0.008150 0.000737 0.002119 -0.008306 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.666989 
40 135.000000 240.000000 8.810395 -5.958263 -0.005052 0.000232 0.002789 -0.005535 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.671243 
41 135.000000 240.000000 8.291299 -5.598357 -0.004420 0.002307 -0.000009 -0.006394 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.690168 
42 135.000000 240.000000 7.372198 -5.302591 -0.004824 0.005417 -0.001717 -0.004670 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.713790 
43 135.000000 240.000000 6.079923 -5.054435 -0.000286 0.003638 -0.001457 -0.002716 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.754161 
44 135.000000 240.000000 5.096429 -3.948571 -0.001133 0.001598 0.000418 -0.001810 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.783196 
45 135.000000 240.000000 4.553761 -3.926883 -0.000655 0.001675 -0.000950 -0.000484 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.812301 
46 135.000000 240.000000 4.603513 -3.526586 -0.000617 0.002016 -0.002057 -0.001797 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.810273 
47 135.000000 240.000000 5.020027 -3.860906 -0.001494 0.001758 -0.000535 0.000667 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.800003 
48 135.000000 240.000000 3.797138 -4.510309 -0.000072 -0.000711 0.003413 -0.000082 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.831255 
49 135.000000 240.000000 2.819207 -3.824162 0.000813 0.001664 0.002158 0.001308 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.862745 
50 135.000000 240.000000 1.478691 -3.219920 0.001954 0.002041 -0.000031 0.000334 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.899574 
51 135.000000 240.000000 1.068122 -2.208663 0.001885 -0.003901 0.005487 0.000970 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.937665 
52 135.000000 240.000000 0.859848 -1.536101 0.002041 -0.002185 0.002680 -0.000055 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.949079 
53 135.000000 240.000000 1.065173 -0.997153 0.001184 -0.002769 0.001563 0.001769 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.958216 
54 135.000000 240.000000 1.297714 -1.621046 0.001056 -0.001849 0.001357 0.001443 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.937863 
55 135.000000 240.000000 1.617242 -2.529494 0.000779 -0.000347 0.000778 0.002566 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.923436 
56 135.000000 240.000000 1.558392 -2.969179 0.000975 0.003767 -0.002869 0.000794 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.919026 
57 135.000000 240.000000 1.573347 -3.173032 0.001449 0.002378 -0.001995 0.001597 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.924233 
58 135.000000 240.000000 1.513758 -2.893473 0.001517 0.001084 0.000272 0.000060 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.931486 
59 135.000000 240.000000 1.020664 -1.975595 0.001036 0.002021 -0.001980 -0.000690 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.958958 
60 135.000000 240.000000 0.916033 -1.334832 0.001354 0.000921 -0.000901 -0.000137 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.965146 
61 135.000000 240.000000 0.786208 -0.919290 0.000588 0.001964 -0.001913 0.000538 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.970263 
62 135.000000 240.000000 0.620806 -0.789169 0.000596 0.001711 -0.002286 -0.000163 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.968833 
63 135.000000 240.000000 0.582419 -0.174640 -0.000188 0.002060 -0.001973 -0.000885 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.978981 
64 135.000000 240.000000 -0.040061 -0.146281 0.000394 0.003077 -0.001094 0.000233 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.986628 
65 135.000000 240.000000 -0.385224 0.053815 0.000391 0.001217 -0.001524 -0.000005 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.978958 
66 135.000000 240.000000 -0.182660 0.132455 0.000025 -0.000973 0.000866 0.000428 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.986211 
67 135.000000 240.000000 -0.289804 0.174725 0.000151 -0.000841 0.000978 0.000457 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.985478 
68 135.000000 240.000000 -0.373971 -0.275516 0.000487 -0.001849 0.001668 0.000595 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.981057 
69 135.000000 240.000000 -0.385081 -0.273254 0.000211 -0.000020 0.000831 -0.000362 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.984329 
70 135.000000 240.000000 -0.229665 0.156399 -0.000035 0.000750 -0.001613 -0.000896 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.988117 
71 135.000000 240.000000 0.070350 0.436400 -0.000647 0.001512 -0.002008 -0.000091 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.988264 
72 135.000000 240.000000 -0.075618 0.409226 -0.000260 0.002116 -0.001828 -0.000469 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.986181 
73 135.000000 240.000000 -0.267306 0.635717 -0.000484 0.001511 -0.002419 -0.000857 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.984779 
74 135.000000 240.000000 -0.291000 0.494453 -0.000428 0.001149 -0.000772 0.000762 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.985247 
75 135.000000 240.000000 -0.272965 0.298851 -0.000313 0.000793 -0.000921 -0.000069 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.987924 
76 135.000000 240.000000 -0.670579 -0.005422 0.000407 0.001976 -0.000504 0.000313 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.982096 
77 135.000000 240.000000 -1.021950 0.132500 0.000260 0.001505 -0.001691 -0.000072 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.976601 
78 135.000000 240.000000 -0.624462 0.386497 -0.000223 0.001731 -0.001924 0.000212 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.979846 
79 135.000000 240.000000 -0.485589 0.243708 -0.000211 0.001772 -0.002095 0.000286 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.983480 
80 135.000000 240.000000 -0.481305 0.374172 -0.000548 0.002276 -0.001750 -0.000095 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.980432 
81 135.000000 240.000000 -0.604752 0.541120 -0.000256 0.002712 -0.002142 -0.000521 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.981343 
82 135.000000 240.000000 -0.884110 0.547841 -0.000137 0.002273 -0.001552 -0.000362 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.971767 
83 135.000000 240.000000 -0.974259 0.405489 0.000183 0.003317 -0.002139 0.000516 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.972609 
84 135.000000 240.000000 -0.916817 0.400890 -0.000135 0.002799 -0.002957 -0.000288 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.976923 
85 135.000000 240.000000 -0.792346 0.403343 -0.000280 0.003010 -0.002378 0.000400 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.976132 
86 135.000000 240.000000 -0.972212 0.337877 -0.000022 0.003086 -0.002503 -0.000217 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.973323 
87 135.000000 240.000000 -1.069092 0.576122 -0.000098 0.002191 -0.001821 -0.000438 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.974522 
88 135.000000 240.000000 -1.260695 0.468652 0.000485 0.002631 -0.001510 0.000699 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.961648 
89 135.000000 240.000000 -1.628406 0.366814 0.000059 0.003046 -0.001758 -0.000155 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.958534 
90 135.000000 240.000000 -1.575739 0.525809 0.000130 0.003679 -0.002658 0.000489 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.955408 
91 135.000000 240.000000 -1.631309 0.374772 0.000375 0.003615 -0.002786 0.000663 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.954606 
92 135.000000 240.000000 -1.598546 0.417313 0.000237 0.004244 -0.002829 0.000427 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.955859 
93 135.000000 240.000000 -1.809409 0.358709 0.000683 0.005499 -0.003547 0.000135 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.946846 
94 135.000000 240.000000 -1.930884 0.527182 0.000724 0.004792 -0.003178 0.000482 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.945290 
95 135.000000 240.000000 -9.508062 3.244276 0.020372 0.099228 0.054058 0.169778 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.297248 
96 135.000000 240.000000 5.457823 0.554367 0.002694 -0.004477 -0.000965 -0.001602 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.826871 
97 135.000000 240.000000 6.395987 1.538342 0.001206 -0.002986 -0.002518 -0.003874 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.784574 
98 135.000000 240.000000 7.114781 2.068962 0.000002 0.001396 -0.006257 -0.002775 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.780933 
99 135.000000 240.000000 7.237963 2.165380 0.001792 0.003473 -0.007194 -0.001892 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.769799 
100 135.000000 240.000000 7.178907 2.133209 0.003309 0.001760 -0.007336 -0.001282 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.788006 
101 135.000000 240.000000 7.014407 1.852815 0.003335 0.002814 -0.008071 -0.001604 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.798895 
102 135.000000 240.000000 7.289155 1.234324 0.004156 -0.002002 -0.005837 -0.000701 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.782028 
103 135.000000 240.000000 7.547078 0.866871 0.001963 -0.001249 -0.003970 -0.001067 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.782435 
104 135.000000 240.000000 7.764035 0.800500 -0.000012 -0.001123 -0.001989 -0.001072 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.762899 
105 135.000000 240.000000 7.664914 0.804881 -0.001712 0.002294 -0.002864 -0.000595 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.766256 
106 135.000000 240.000000 7.712976 0.594894 -0.002587 0.002291 -0.003427 -0.001662 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.764091 
107 135.000000 240.000000 8.118211 0.455503 -0.001817 0.002946 -0.003090 0.001614 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.758922 
108 135.000000 240.000000 8.084123 -0.033045 -0.001256 0.002167 -0.002503 0.001630 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.752927 
109 135.000000 240.000000 8.110596 -0.287705 -0.001893 0.000034 -0.000895 0.001672 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.742354 
110 135.000000 240.000000 8.408469 -0.514781 -0.000982 0.000198 -0.001354 0.003389 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.721086 
111 135.000000 240.000000 8.317589 -1.088017 0.001070 0.002771 -0.003892 0.004678 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.716189 
112 135.000000 240.000000 8.562816 -1.331015 -0.003932 0.002840 -0.005449 0.001287 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.690756 
113 135.000000 240.000000 9.346880 -1.452688 -0.003654 0.002480 -0.006390 0.003184 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.675586 
114 135.000000 240.000000 9.980374 -2.372432 -0.000597 -0.001682 -0.004613 0.003968 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.649998 
115 135.000000 240.000000 9.862876 -3.283352 -0.001854 -0.002676 -0.003773 -0.001607 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.609451 
116 135.000000 240.000000 10.367447 -3.734258 -0.002535 -0.002305 -0.005267 0.002519 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.606372 
117 135.000000 240.000000 11.021116 -3.966478 -0.001299 -0.003116 -0.002966 0.000609 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.577099 
118 135.000000 240.000000 11.113354 -4.458882 -0.002723 -0.000915 -0.003150 -0.005738 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.582261 
119 135.000000 240.000000 10.956777 -4.972813 -0.004886 0.001537 -0.000170 -0.009398 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.582657 
120 135.000000 240.000000 10.399890 -4.721528 -0.003309 0.002040 0.000031 -0.008634 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.592078 
121 135.000000 240.000000 9.846274 -4.999029 -0.006340 -0.000845 0.003737 -0.008019 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.602652 
122 135.000000 240.000000 9.723545 -5.145399 -0.004537 0.000700 0.004295 -0.008621 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.624047 
123 135.000000 240.000000 9.687957 -5.250859 -0.004909 0.000507 0.004980 -0.012351 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.636545 
124 135.000000 240.000000 9.107303 -5.703803 -0.005049 -0.001506 0.005097 -0.007167 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.658154 
125 135.000000 240.000000 8.831496 -6.665693 -0.003729 -0.007480 0.005986 -0.011287 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.676202 
126 135.000000 240.000000 8.912755 -6.768692 -0.006112 -0.007662 0.007706 -0.010891 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.681434 
127 135.000000 240.000000 8.283004 -6.353564 -0.006192 -0.006970 0.005881 -0.011102 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.697670 
128 135.000000 240.000000 7.737583 -5.414792 -0.005618 -0.010676 0.004402 -0.005596 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.726253 
129 135.000000 240.000000 7.732482 -4.403181 -0.005846 -0.010350 0.002491 -0.002835 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.741396 
130 135.000000 240.000000 7.817722 -4.621673 -0.005798 -0.007739 0.000291 0.000189 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.744369 
131 135.000000 240.000000 8.129104 -6.124108 -0.006003 -0.008460 -0.001035 -0.002151 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.749008 
132 135.000000 240.000000 8.078376 -6.733181 -0.004403 -0.008378 0.001314 -0.000917 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.743056 
133 135.000000 240.000000 6.939256 -6.627433 -0.004106 -0.005009 -0.000074 -0.001250 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.763456 
134 135.000000 240.000000 6.373483 -5.985929 -0.004670 -0.004686 0.002507 -0.002982 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.783707 
135 135.000000 240.000000 5.409969 -5.442046 -0.006470 -0.001689 0.002652 -0.004123 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.806794 
136 135.000000 240.000000 4.725564 -4.563665 -0.003180 -0.001306 0.001579 -0.003164 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.826070 
137 135.000000 240.000000 4.150312 -3.543770 -0.002786 -0.000165 0.001075 -0.002917 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.852923 
138 135.000000 240.000000 3.798083 -2.840082 -0.003464 -0.001818 0.002233 -0.002394 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.859887 
139 135.000000 240.000000 3.189457 -2.855798 -0.002825 -0.000386 0.002904 -0.002004 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.864847 
140 135.000000 240.000000 3.413115 -2.484658 -0.003086 -0.001101 0.002064 -0.002044 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.865938 
141 135.000000 240.000000 3.012803 -2.575605 -0.002580 0.001860 0.003186 -0.002107 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.882859 
142 135.000000 240.000000 2.251468 -1.841935 -0.000417 0.001995 0.002100 -0.002853 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.907703 
143 135.000000 240.000000 1.997470 -1.219295 -0.001003 0.002352 0.002183 -0.002848 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.938087 
144 135.000000 240.000000 1.547633 -0.466325 -0.000486 0.001387 -0.000078 -0.004524 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.947630 
145 135.000000 240.000000 1.458625 -0.028613 -0.001035 0.000286 0.001311 -0.001113 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.965352 
146 135.000000 240.000000 0.959842 -0.193091 0.000065 0.001859 -0.000290 -0.001787 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.973023 
147 135.000000 240.000000 0.446331 0.023004 -0.000356 0.001288 -0.000562 -0.000495 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.969228 
148 135.000000 240.000000 0.640987 0.006590 -0.000093 0.002285 -0.002328 -0.000305 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.980934 
149 135.000000 240.000000 0.441757 -0.256641 -0.000081 0.005379 -0.005310 -0.000948 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.983112 
150 135.000000 240.000000 1.023907 0.074890 -0.000776 0.001303 -0.001194 -0.000452 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.977776 
151 135.000000 240.000000 0.302585 -0.004172 -0.000160 0.001643 0.000352 -0.000357 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.985856 
152 135.000000 240.000000 -0.265671 0.507791 0.000120 0.000839 -0.002363 -0.000866 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.981057 
153 135.000000 240.000000 -0.513091 0.817634 -0.000321 0.000013 -0.001435 0.000765 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.979948 
154 135.000000 240.000000 -0.410575 0.558842 -0.000003 0.000260 -0.001056 0.002788 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.979115 
155 135.000000 240.000000 -0.567732 0.269610 0.000222 0.000736 -0.001998 -0.000039 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.980077 
156 135.000000 240.000000 -0.328931 0.470920 -0.000050 0.000844 -0.002300 0.000504 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.982448 
157 135.000000 240.000000 -0.214628 0.486600 -0.000423 0.001768 -0.003083 0.000479 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.984920 
158 135.000000 240.000000 -0.304038 0.426275 -0.000144 0.001963 -0.002361 0.000261 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.982228 
159 135.000000 240.000000 -0.801216 0.576850 0.000047 0.001524 -0.002043 0.001917 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.979093 
160 135.000000 240.000000 -1.122656 0.564923 0.000337 0.000220 -0.001496 0.001938 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.975636 
161 135.000000 240.000000 -1.325414 0.667236 0.000586 0.000645 -0.002133 0.000384 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.958010 
162 135.000000 240.000000 -1.034628 1.193535 -0.000437 -0.000091 -0.003032 0.002088 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.968289 
163 135.000000 240.000000 -1.140076 0.751310 0.000075 0.000637 -0.001636 0.002153 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.972588 
164 135.000000 240.000000 -1.539310 0.680228 0.001051 0.000050 -0.000346 0.003236 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.956888 
165 135.000000 240.000000 -1.748384 0.698350 0.000585 0.001236 -0.002950 0.001296 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.953226 
166 135.000000 240.000000 -1.632254 0.649103 0.000721 0.002198 -0.002577 0.002825 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.953834 
167 135.000000 240.000000 -1.558822 0.873421 0.000570 0.001491 -0.003737 0.001548 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.953715 
168 135.000000 240.000000 -1.513270 0.792343 0.000282 0.001844 -0.002184 0.001811 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.958512 
169 135.000000 240.000000 -1.950586 0.714381 0.000980 0.001505 -0.002498 0.003042 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.948324 
170 135.000000 240.000000 -26.790123 33.916080 -0.007902 0.069387 -0.040963 0.170243 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.137459 
171 135.000000 240.000000 3.801704 -1.313934 0.003428 0.001358 -0.002944 0.004307 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.879558 
172 135.000000 240.000000 3.813680 -1.201238 0.002740 0.001288 -0.002440 0.003971 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.869971 
173 135.000000 240.000000 4.044944 -1.019858 0.002392 0.001483 -0.002099 0.003499 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.848528 
174 135.000000 240.000000 4.227201 -0.802894 0.002342 0.001098 -0.001781 0.004657 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.843124 
175 135.000000 240.000000 4.196858 -0.797057 0.003294 0.000269 -0.000591 0.004922 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.841272 
176 135.000000 240.000000 4.493222 -0.874241 0.002438 -0.000765 0.000252 0.005290 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.826643 
177 135.000000 240.000000 4.748622 -1.051778 0.004016 -0.000843 -0.000048 0.006087 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.802364 
178 135.000000 240.000000 5.619079 -1.261059 0.003222 -0.000945 0.001276 0.006298 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.769120 
179 135.000000 240.000000 6.772957 -1.011293 0.003646 -0.001019 0.000943 0.007301 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.721078 
180 135.000000 240.000000 7.861742 -1.069133 0.005600 0.001045 0.000114 0.008560 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.683953 
181 135.000000 240.000000 8.501385 -1.187390 0.003694 0.003816 0.000144 0.007306 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.654610 
182 135.000000 240.000000 9.050742 -1.168259 0.004879 0.004841 0.000447 0.007938 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.638270 
183 135.000000 240.000000 9.737406 -0.145024 0.003092 0.003927 -0.000476 0.004652 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.614091 
184 135.000000 240.000000 10.475440 0.797998 0.001934 0.006627 0.000043 0.005202 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.589182 
185 135.000000 240.000000 11.188780 1.527593 0.001270 0.005818 0.000528 0.006680 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.571415 
186 135.000000 240.000000 12.056089 1.378513 0.000365 0.003486 -0.003845 0.008698 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.546278 
187 135.000000 240.000000 12.885818 0.864743 0.000487 0.005818 -0.003930 0.008006 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.542667 
188 135.000000 240.000000 13.120882 0.415419 -0.001728 0.005460 -0.003617 0.003396 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.550614 
189 135.000000 240.000000 13.298791 0.365352 0.000050 0.002508 -0.005334 0.005013 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.535315 
190 135.000000 240.000000 13.220395 0.467171 0.001188 -0.000211 -0.004332 0.000108 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.571156 
191 135.000000 240.000000 13.276840 0.514733 0.000851 -0.000167 -0.001305 -0.001999 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.579507 
192 135.000000 240.000000 13.279358 0.187074 0.002298 -0.000215 -0.001359 -0.001317 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.581093 
193 135.000000 240.000000 13.385923 -0.294093 0.004464 0.000149 -0.001349 -0.003790 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.577531 
194 135.000000 240.000000 13.450600 -0.874191 0.004428 -0.000479 -0.002714 -0.002983 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.579129 
195 135.000000 240.000000 13.351054 -0.915408 0.009294 -0.000183 -0.005492 -0.001217 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.612295 
196 135.000000 240.000000 13.493741 -1.195124 0.004748 -0.000499 -0.007002 -0.000872 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.614763 
197 135.000000 240.000000 13.903526 -1.570275 0.001787 -0.001294 -0.005086 -0.002074 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.620968 
198 135.000000 240.000000 14.039480 -1.909456 -0.000910 0.000702 -0.001193 -0.000928 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.633556 
199 135.000000 240.000000 13.596064 -1.875187 0.000411 0.000744 -0.001090 -0.000865 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.652563 
200 135.000000 240.000000 13.313745 -1.871269 0.000758 0.002857 -0.001304 0.002556 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.651649 
201 135.000000 240.000000 13.107425 -1.877411 0.004473 -0.000093 -0.002293 0.005049 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.641091 
202 135.000000 240.000000 13.864391 -2.637830 -0.004224 -0.005555 -0.002605 0.003879 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.592888 
203 135.000000 240.000000 13.733225 -2.819987 -0.003643 -0.006560 -0.004448 0.002892 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.587470 
204 135.000000 240.000000 14.150277 -3.217538 -0.005895 0.000306 -0.005656 -0.003018 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.555005 
205 135.000000 240.000000 14.609234 -3.411526 -0.006328 0.002368 -0.005342 -0.011806 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.538900 
206 135.000000 240.000000 14.871439 -3.436735 -0.005914 0.001015 -0.005008 -0.016241 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.542979 
207 135.000000 240.000000 14.449788 -3.807685 -0.009857 -0.000081 -0.005787 -0.012188 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.545478 
208 135.000000 240.000000 13.302573 -4.321957 -0.011970 -0.000041 -0.000157 -0.011923 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.562123 
209 135.000000 240.000000 11.788564 -4.879584 -0.004755 -0.004501 0.002642 -0.005504 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.601514 
210 135.000000 240.000000 10.165008 -4.273910 -0.006286 -0.004860 0.006147 -0.007258 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.633347 
211 135.000000 240.000000 9.717595 -4.183448 -0.005280 -0.004750 0.006934 -0.004085 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.649046 
212 135.000000 240.000000 8.851028 -4.799056 -0.010610 -0.007452 0.005595 -0.007783 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.674779 
213 135.000000 240.000000 8.605553 -4.669561 -0.009071 -0.007028 0.003479 -0.004439 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.668723 
214 135.000000 240.000000 8.741680 -3.764060 -0.010136 -0.007663 0.001490 -0.006864 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.682881 
215 135.000000 240.000000 8.791475 -3.531535 -0.013738 -0.003687 0.001886 -0.002447 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.686838 
216 135.000000 240.000000 7.996806 -3.490895 -0.008326 -0.004476 0.001483 -0.004261 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.723070 
217 135.000000 240.000000 7.026319 -3.364888 -0.004601 -0.009495 0.004331 -0.001555 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.759067 
218 135.000000 240.000000 6.671208 -4.045052 -0.003464 -0.010642 0.007755 -0.000906 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.761173 
219 135.000000 240.000000 6.093973 -3.993242 -0.001021 -0.013320 0.010402 -0.000386 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.790122 
220 135.000000 240.000000 5.549412 -3.849805 -0.002299 -0.010158 0.007570 -0.002564 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.797763 
221 135.000000 240.000000 6.090768 -3.581337 -0.003924 -0.007784 0.002744 -0.003112 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.794412 
222 135.000000 240.000000 7.164051 -3.531178 -0.002365 -0.004590 -0.002073 -0.002842 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.728177 
223 135.000000 240.000000 7.343037 -3.729810 -0.006239 -0.001186 -0.001955 -0.002572 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.793666 
224 135.000000 240.000000 6.411927 -3.933058 -0.006547 -0.001976 0.003953 -0.002981 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.798683 
225 135.000000 240.000000 4.847088 -4.643100 -0.005793 -0.002387 0.007800 -0.001982 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.819980 
226 135.000000 240.000000 4.021071 -3.227367 -0.002481 -0.005439 0.007085 -0.004347 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.847763 
227 135.000000 240.000000 3.743378 -1.775434 -0.006771 -0.005816 0.007289 -0.003822 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.849411 
228 135.000000 240.000000 4.025612 -1.622956 -0.004734 -0.006009 0.007449 -0.002409 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.840585 
229 135.000000 240.000000 3.644088 -1.027289 -0.003534 -0.000892 0.004035 -0.004081 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.854183 
230 135.000000 240.000000 2.668117 -0.930049 -0.003933 0.002195 0.002380 -0.001262 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.883200 
231 135.000000 240.000000 2.301863 -1.997831 -0.001326 0.002723 0.003142 0.000268 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.891213 
232 135.000000 240.000000 1.963917 -1.772491 -0.000982 0.002704 0.000176 -0.003500 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.910982 
233 135.000000 240.000000 2.259010 -0.874835 -0.001382 0.003352 0.000440 -0.003098 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.909175 
234 135.000000 240.000000 1.367538 -0.172402 -0.000822 0.003453 -0.001926 -0.002209 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.948762 
235 135.000000 240.000000 1.295393 -0.295685 -0.000190 0.002682 -0.001676 -0.000895 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.954001 
236 135.000000 240.000000 1.226769 -0.488073 -0.000718 0.003594 -0.002134 -0.001574 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.957358 
237 135.000000 240.000000 0.993909 -0.146737 -0.000457 0.003666 -0.002833 -0.001915 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.968030 
238 135.000000 240.000000 0.757257 0.102535 -0.000381 0.000940 -0.000366 -0.000742 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.975293 
239 135.000000 240.000000 0.025777 0.056541 0.000238 0.000559 -0.000079 0.000651 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.000000 0.985417 