
//ƒƒ‚ƒŠ‰ð•ú—pƒ}ƒNƒ
#define _DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define _DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define _RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#define _FREE(p)		 { if(p) { free(p); p=NULL; } }

