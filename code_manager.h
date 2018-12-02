/**************
Code Placer
**************/

int data_offset = 3;

//allocates space for one symbol
int data_locate(){
	return data_offset++;
}

int code_offset = 0;

//returns current offset
int get_label(){
	return code_offset;
}
//allocates space for one line of code
int code_allocate(){
	//if(code_offset+1==888 || code_offset+1==8888 || code_offset+1==8889)
		//code_offset+=2;
		//else
	return code_offset++;
}

//generates code at current location
void gen_code(enum assm_ops operation, int arg){
	code[code_offset].op = operation;
    if(operation==JUMP)
	code[code_offset].arg = arg;
    else
code[code_offset].arg = arg+64;
    code[code_offset++].arg2 = -1;
}
//generates code at current location
void gen_code2(enum assm_ops operation, int arg,int arg2){
	code[code_offset].op = operation;
 if(operation==HALT)
code[code_offset].arg = arg;

else
code[code_offset].arg = arg+64;
    if(operation==COPY || operation==ADD || operation==SUB || operation==READ || operation==WRITE)
code[code_offset++].arg2 = arg2+64;
else
code[code_offset++].arg2 = arg2;
}

//generates code at previously reserved location
void back_patch(int addr, enum assm_ops operation, int arg){
	code[addr].op = operation;
	code[addr].arg = arg;
}

//prints machine code to given file
void print_code(FILE* out){
	for(int i=0; i<code_offset; i++)
    {
		if(code[i].arg < 0)
			fprintf(out,"%-10d\n",op_name[code[i].op]);
		else if (code[i].arg2<=0)
        {
            if(code[i].op==JUMP)
			    fprintf(out,"%-10s%4d\n",op_name[code[i].op], code[i].arg);
            else
                fprintf(out,"%-10s%4c\n",op_name[code[i].op], code[i].arg);
        }
        else
        {
            if(code[i].op==JZERO || code[i].op==JODD)
			    fprintf(out,"%-10s%4c%4d\n",op_name[code[i].op], code[i].arg,code[i].arg2);
            else if (code[i].op==COPY || code[i].op==ADD || code[i].op==SUB)
                fprintf(out,"%-10s%4c%4c\n",op_name[code[i].op], code[i].arg,code[i].arg2);    
            
            else
                fprintf(out,"%-10s%4d%4d\n",op_name[code[i].op], code[i].arg,code[i].arg2);
        }
    }
}