extern void
MakeTable_begin(const char *tableName,
                const char *fileName, 
                const char *tableType,
                int tableSize);

extern void
MakeTable_comment(const char *commentString);

extern void
MakeTable_extraCode(const char *codeString);

extern void 
MakeTable_outputString(const char *string);

#ifdef USE_INT64
  extern void 
  MakeTable_outputUInt64(uint64 arg);
#endif

extern void 
MakeTable_outputUInt32(uint32 arg);

extern void 
MakeTable_outputUInt16(uint16 arg);

extern void 
MakeTable_outputUInt8(uint8 arg);

extern void 
MakeTable_end(void);
    

extern uint32 n_bits_func(uint32 arg);
extern uint32 top_card_func(uint32 arg);
extern uint32 bottom_card_func(uint32 arg);
extern uint32 bottom_bit_func(uint32 arg);
extern uint32 top_bit_func(uint32 arg);
extern uint32 straight_func(uint32 arg);
