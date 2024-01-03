#include <stdio.h>
#include <windows.h>


/* opt_idx数组 由Optimize_Array()函数生成 */
const unsigned int opt_idx[] = {
     0, 4951,   9950, 289,  10604, 277,  11254, 268,  11902, 261,  12548, 255,  13194, 249,  13840, 243,
 14486, 238,  15130, 234,  15774, 230,  16418, 226,  17062, 222,  17706, 218,  18350, 214,  18994, 211,
 19636, 208,  20280, 204,  20924, 201,  21566, 199,  22208, 196,  22852, 193,  23494, 191,  24136, 188,
 24780, 185,  25422, 183,  26064, 181,  26706, 179,  27348, 177,  27990, 175,  28632, 173,  29274, 171,
 29916, 169,  30558, 167,  31200, 165,  31842, 163,  32484, 161,  33126, 159,  33768, 157,  34410, 156,
 35050, 155,  35692, 153,  36334, 151,  36976, 150,  37616, 149,  38258, 147,  38900, 145,  39542, 144,
 40182, 143,  40824, 142,  41464, 141,  42106, 139,  42748, 138,  43388, 137,  44030, 136,  44670, 135,
 45312, 134,  45952, 133,  46594, 132,  47234, 131,  47876, 130,  48516, 129,  49158, 128,  49798, 127,
 50440, 126,  51080, 125,  51722, 124,  52362, 124,  53002, 123,  53644, 122,  54284, 122,  54924, 121,
 55566, 120,  56206, 120,  56846, 119,  57488, 118,  58128, 118,  58768, 117,  59410, 116,  60050, 116,
 60690, 116,  61330, 115,  61972, 114,  62612, 114,  63252, 114,  63892, 114,  64532, 113,  65174, 112,
 65814, 112,  66454, 112,  67094, 112,  67734, 112,  68374, 112,  69014, 111,  69656, 110,  70296, 110,
 70936, 110,  71576, 110,  72216, 110,  72856, 110,  73496, 110,  74136, 110,  74776, 110,  75416, 110,
 76056, 110,  76696, 110,  77336, 110,  77976, 110,  78616, 110,  79256, 110,  79896, 110,  80536, 110,
 81176, 110,  81816, 110,  82456, 110,  83096, 110,  83736, 110,  84376, 111,  85014, 112,  85654, 112,
 86294, 112,  86934, 112,  87574, 112,  88214, 112,  88854, 113,  89492, 114,  90132, 114,  90772, 114,
 91412, 114,  92052, 115,  92690, 116,  93330, 116,  93970, 116,  94610, 117,  95248, 118,  95888, 118,
 96528, 119,  97166, 120,  97806, 120,  98446, 121,  99084, 122,  99724, 122, 100364, 123, 101002, 124,
101642, 124, 102282, 125, 102920, 126, 103560, 127, 104198, 128, 104838, 129, 105476, 130, 106116, 131,
106754, 132, 107394, 133, 108032, 134, 108672, 135, 109310, 136, 109950, 137, 110588, 138, 111228, 139,
111866, 141, 112504, 142, 113144, 143, 113782, 144, 114422, 145, 115060, 147, 115698, 149, 116336, 150,
116976, 151, 117614, 153, 118252, 155, 118890, 156, 119530, 157, 120168, 159, 120806, 161, 121444, 163,
122082, 165, 122720, 167, 123358, 169, 123996, 171, 124634, 173, 125272, 175, 125910, 177, 126548, 179,
127186, 181, 127824, 183, 128462, 185, 129100, 188, 129736, 191, 130374, 193, 131012, 196, 131648, 199,
132286, 201, 132924, 204, 133560, 208, 134196, 211, 134834, 214, 135470, 218, 136106, 222, 136742, 226,
137378, 230, 138014, 234, 138650, 238, 139286, 243, 139920, 249, 140554, 255, 141188, 261, 141822, 268,
142454, 277, 143084, 289, 143710, 4945,
};



/************* Need to Be Modified ***********/
extern  unsigned char       gImage_FaFa[153600];
#define BACK_GROUND_ARRAY   gImage_FaFa
extern  unsigned char       gImage_Mask[153600];
#define FORE_GROUND_ARRAY   gImage_Mask
#define COLOR_LSB           0x41
#define COLOR_MSB           0x08
/**************** Need to Modify **************/
#define ARRAY_LEN       sizeof(FORE_GROUND_ARRAY)/sizeof(unsigned char)


void Optimize_Array(unsigned char *array, int len, unsigned char colorHex)
{
    int cnt = 0, same = 1;
    int i, j;

    for(i=0; i<len; i++)
    {
        if(array[i] == colorHex)
        {
            printf("%6d, ", i);
            for(j=i; j<len; j+=2)
            {
                if(array[j+2] == colorHex)
                    same++;
                else 
                {
                    i = j;
                    break;
                }
            }
            printf("%2d, ", same);
            same = 1;
            if(++cnt %8 == 0)
            printf("\n");
        }
    }
    printf("\r\n\n");
    printf("########## Raw Len: [%d]\n", len);
    printf("########## Opt Len: [%d]\r\n\n", cnt*sizeof(unsigned int));
    printf("========== Raw/Opt: [%d]\n", len / (cnt*sizeof(unsigned int)));
    printf("\r\n\n");
}


void Merge_Beauty_Img(void *buf)
{
    if(!buf)
        return;
    unsigned char *buf_raw = (unsigned char*)buf;

    int idxLen = sizeof(opt_idx)/sizeof(unsigned int);
    int cnt, same;

    for(cnt=0; cnt<idxLen; cnt+=2)
    {
        for(same=0; same<opt_idx[cnt+1]; same++)
        {
            /* 不带Alpha通道，直接覆盖前景色 */
            buf_raw[opt_idx[cnt] + 2*same]    = COLOR_LSB;
            buf_raw[opt_idx[cnt] + 2*same +1] = COLOR_MSB;
        }
    }
    printf("==========Beauty ok.\r\n");
}


/******************** [RGBA透明度混合算法AlphaBlend] ******************
 * 
 * 有一幅图像是A，另一幅透明图像是B，透过B去看A，B和A的混合图像是图像C
 * 图像B的透明度是alpha (值域0-0xff，0为完全透明，ff为完全不透明)
 * 计算图像C的混合公式如下：
 * R(C) = alpha*R(B) + (0xff-alpha)*R(A)
 * G(C) = alpha*G(B) + (0xff-alpha)*G(A)
 * B(C) = alpha*B(B) + (0xff-alpha)*B(A)
 * 
 * 参考：https://www.cnblogs.com/oloroso/p/10724803.html
 ********************************************************************/
void Merge_Beauty_Img_Alpha(void *buf, unsigned char alpha)
{
    if(!buf)
        return;
    unsigned char *buf_raw = (unsigned char*)buf;

    int idxLen = sizeof(opt_idx)/sizeof(unsigned int);
    int cnt, same;
    unsigned char Rb, Gb, Bb; //前景色
    unsigned char Ra, Ga, Ba; //背景色
    unsigned short RGB565_b, RGB565_Alpha_b; //前景色
    unsigned short RGB565_a, RGB565_Alpha_a; //背景色

    for(cnt=0; cnt<idxLen; cnt+=2)
    {
        for(same=0; same<opt_idx[cnt+1]; same++)
        {
            /* [前景色] 16位RGB565 */
            RGB565_b = ((unsigned short)COLOR_MSB<<8)|COLOR_LSB;
            /* [前景色] R/G/B通道拆分 */
            Rb = (RGB565_b & 0xF800) >> 11;
            Gb = (RGB565_b & 0x07E0) >> 5;
            Bb = (RGB565_b & 0x001F);
            /* [前景色] 三通道分别设置alpha值(透明度) */
            Rb = (Rb * alpha) >> 8;
            Gb = (Gb * alpha) >> 8;
            Bb = (Bb * alpha) >> 8;
            /* [前景色] 将R/G/B三通道组装回16位RGB565(已带Alpha通道) */
            RGB565_Alpha_b = ((unsigned short)Rb<<11) | ((unsigned short)Gb<<5) | (unsigned short)Bb;
            
            /* [背景色] 16位RGB565 */
            RGB565_a = ((unsigned short)(buf_raw[opt_idx[cnt] + 2*same +1])<<8) | (buf_raw[opt_idx[cnt] + 2*same]);
            /* [背景色] R/G/B通道拆分 */
            Ra = (RGB565_a & 0xF800) >> 11;
            Ga = (RGB565_a & 0x07E0) >> 5;
            Ba = (RGB565_a & 0x001F);
            /* [背景色] 三通道分别设置alpha值(透明度) */
            Ra = (Ra * (0xFF - alpha)) >> 8;
            Ga = (Ga * (0xFF - alpha)) >> 8;
            Ba = (Ba * (0xFF - alpha)) >> 8;
            /* [背景色] 将R/G/B三通道组装回16位RGB565(已带Alpha通道) */
            RGB565_Alpha_a = ((unsigned short)Ra<<11) | ((unsigned short)Ga<<5) | (unsigned short)Ba;

            /* 叠加带有Alpha通道的前景色+背景色 */
            buf_raw[opt_idx[cnt] + 2*same]    = (RGB565_Alpha_b & 0x00FF) | (RGB565_Alpha_a & 0x00FF);
            buf_raw[opt_idx[cnt] + 2*same +1] = (RGB565_Alpha_b & 0xFF00) >>8 | (RGB565_Alpha_a & 0xFF00) >>8;
        }
    }
    printf("==========Beauty ok.\r\n");
}


void Output_Beauty_TXT_for_Verify(unsigned char *hexBuf, char *path)
{
    int cnt;
    unsigned char *pOutStr = (unsigned char *)malloc(ARRAY_LEN*6);

    for(cnt=0; cnt<ARRAY_LEN; cnt++)
    {
        sprintf(pOutStr+cnt*5, "0X%02X,", hexBuf[cnt]);
    }
    FILE* fd = fopen(path, "w+");
    for(cnt=0; cnt<ARRAY_LEN/16; cnt++)
    {
        fwrite(pOutStr, 16*5, 1, fd);
        fwrite("\n", 1, 1, fd);
        pOutStr += 16*5;
    }
    fclose(fd);
    printf("==========Save file to [%s] OK.\r\n", path);
}

void Output_Beauty_HEX_for_Verify(unsigned char *hexBuf, char *path)
{
    FILE* fd = fopen(path, "wb+");
    fwrite(hexBuf, ARRAY_LEN, 1, fd);
    fclose(fd);
    printf("==========Save file to [%s] OK.\r\n\n", path);
}



/*******************************************使用方法***********************************************
**step1: 将要合入的png前景图，放在一张纯色320*240的图上，然后用Img2Lcd工具取模。
**step2: 将step1得到的数组，填入Optimize_Array()函数处理，得到优化数组opt_idx，内存占用大大减少。
**step3: 将opt_idx和Merge_Beauty_Img_Buf()函数放入最终代码，函数入参uint8*类型的背景图RGB格式数据的指针，即可Merge成功。
**************************************************************************************************/
int main()
{
#if 0
    /* 生成前景图的内存优化数组，通过调试窗口输出 */
    Optimize_Array(FORE_GROUND_ARRAY, ARRAY_LEN, COLOR_LSB);

#else
    /* 将优化数组merge到背景图中，使背景图上面叠加前景图 */
    // Merge_Beauty_Img(BACK_GROUND_ARRAY);
    Merge_Beauty_Img_Alpha(BACK_GROUND_ARRAY, 60); //绿色透明度136效果最好(过大透明效果不明显，过小会失真)

    /* 将merge后的数组输出到文件，验证结果正确性 */
    // Output_Beauty_TXT_for_Verify(BACK_GROUND_ARRAY, "Output_TXT.txt");
    Output_Beauty_HEX_for_Verify(BACK_GROUND_ARRAY, "C:\\Users\\jerry.chen\\Desktop\\IMG\\Output_HEX.img");
#endif

    system("pause");
    return 0;
}

