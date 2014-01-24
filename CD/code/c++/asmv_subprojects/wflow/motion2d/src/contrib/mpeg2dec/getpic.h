#ifdef MPEG_SHOTS
extern t_MVMatrix *MVMatrixArrayForward, *MVMatrixArrayBackward, *dc_dct;
#endif
/* private prototypes*/
static void picture_data _ANSI_ARGS_((int framenum));
static void macroblock_modes _ANSI_ARGS_((int *pmacroblock_type, int *pstwtype,
  int *pstwclass, int *pmotion_type, int *pmotion_vector_count, int *pmv_format, int *pdmv,
  int *pmvscale, int *pdct_type));
static void Clear_Block _ANSI_ARGS_((int comp));
static void Sum_Block _ANSI_ARGS_((int comp));
static void Saturate _ANSI_ARGS_((short *bp));
static void Add_Block _ANSI_ARGS_((int comp, int bx, int by,
  int dct_type, int addflag));
static void Update_Picture_Buffers _ANSI_ARGS_((void));
static void frame_reorder _ANSI_ARGS_((int bitstream_framenum,
  int sequence_framenum));
static void Decode_SNR_Macroblock _ANSI_ARGS_((int *SNRMBA, int *SNRMBAinc,
  int MBA, int MBAmax, int *dct_type));

static void motion_compensation _ANSI_ARGS_((int MBA, int macroblock_type,
 int motion_type, int PMV[2][2][2], int motion_vertical_field_select[2][2],
 int dmvector[2], int stwtype, int dct_type));

static void skipped_macroblock _ANSI_ARGS_((int dc_dct_pred[3],
  int PMV[2][2][2], int *motion_type, int motion_vertical_field_select[2][2],
  int *stwtype, int *macroblock_type));

static int slice _ANSI_ARGS_((int framenum, int MBAmax));

static int start_of_slice _ANSI_ARGS_ ((int MBAmax, int *MBA,
  int *MBAinc, int dc_dct_pred[3], int PMV[2][2][2]));

static int decode_macroblock _ANSI_ARGS_((int *macroblock_type,
  int *stwtype, int *stwclass, int *motion_type, int *dct_type,
  int PMV[2][2][2], int dc_dct_pred[3],
  int motion_vertical_field_select[2][2], int dmvector[2]));
