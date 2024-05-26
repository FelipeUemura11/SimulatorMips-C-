#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Opcodes -> Valores em decimal que o processador vai ler e entender qual sera a operacao
#define ADD 32
#define SUB 34
#define OR  36
#define AND 37
#define SLT 42
#define BNE 4
#define BEQ 5
#define J   2
#define JR  8
#define LW  35
#define SW  43

// Registradores -> Valores dos registradores em decimal que o processador ira ler e entender qual sera a operacao
#define $zero 0
#define $at 1
#define $v0 2
#define $v1 3
#define $a0 4
#define $a1 5
#define $a2 6
#define $a3 7
#define $t0 8
#define $t1 9
#define $t2 10
#define $t3 11
#define $t4 12
#define $t5 13
#define $t6 14
#define $t7 15
#define $s0 16
#define $s1 17
#define $s2 18
#define $s3 19
#define $s4 20
#define $s5 21
#define $s6 22
#define $s7 23
#define $t8 24
#define $t9 25
#define $k0 26
#define $k1 27
#define $gp 28
#define $sp 29
#define $fp 30
#define $ra 31

// Dados dos formato das instrucoes

struct Instrucao{
	int opcode;
	int rs;
	int rt;
	int rd;
	int shamt;
	int funct;
	int enderecoImediato;
	int enderecoDestino;
};

// Selecao do opcode
int selecionaOpcode(){

	int op;

	printf("  Opcoes de opcode: \n");
	printf("  1. ADD\n");
	printf("  2. SUB\n");
	printf("  3. OR\n");
	printf("  4. AND\n");
	printf("  5. SLT\n");
	printf("  6. BNE\n");
	printf("  7. BEQ\n");
	printf("  8. J\n");
	printf("  9. JR\n");
	printf("  10. LW\n");
	printf("  11. SW\n");
	printf("  Selecione a opcao de opcode: ");
	scanf("%d", &op);

	switch(op){
		case 1:
			return ADD;
		case 2:
			return SUB;
		case 3:
			return OR;
		case 4:
			return AND;
		case 5:
			return SLT;
		case 6:
			return BNE;
		case 7:
			return BEQ;
		case 8:
			return J;
		case 9:
			return JR;
		case 10:
			return LW;
		case 11:
			return SW;
		default:
			printf("Opcao invalida!");
	}
	return 0;
}

// Selecao de registrador
int selecionaRegistrador(){

	int reg;

	printf("  Opcoes de registrador: \n");
	printf("  0. $zero\n");
	printf("  1. $at\n");
	printf("  2. $v0\n");
	printf("  3. $v1\n");
	printf("  4. $a0\n");
	printf("  5. $a1\n");
	printf("  6. $a2\n");
	printf("  7. $a3\n");
	printf("  8. $t0\n");
	printf("  9. $t1\n");
	printf("  10. $t2\n");
	printf("  11. $t3\n");
	printf("  12. $t4\n");
	printf("  13. $t5\n");
	printf("  14. $t6\n");
	printf("  15. $t7\n");
	printf("  16. $s0\n");
	printf("  17. $s1\n");
	printf("  18. $s2\n");
	printf("  19. $s3\n");
	printf("  20. $s4\n");
	printf("  21. $s5\n");
	printf("  22. $s6\n");
	printf("  23. $s7\n");
	printf("  24. $t8\n");
	printf("  25. $t9\n");
	printf("  26. $k0\n");
	printf("  27. $k1\n");
	printf("  28. $gp\n");
	printf("  29. $sp\n");
	printf("  30. $fp\n");
	printf("  31. $ra\n");
	printf("  Selecione a opcao de registrador: ");
	scanf("%d", &reg);

	switch(reg){
		case 0:
			return $zero;
		case 1:
			return $at;
		case 2:
			return $v0;
		case 3:
			return $v1;
		case 4:
			return $a0;
		case 5:
			return $a1;
		case 6:
			return $a2;
		case 7:
			return $a3;
		case 8:
			return $t0;
		case 9:
			return $t1;
		case 10:
			return $t2;
		case 11:
			return $t3;
		case 12:
			return $t4;
		case 13:
			return $t5;
		case 14:
			return $t6;
		case 15:
			return $t7;
		case 16:
			return $s0;
		case 17:
			return $s1;
		case 18:
			return $s2;
		case 19:
			return $s3;
		case 20:
			return $s4;
		case 21:
			return $s5;
		case 22:
			return $s6;
		case 23:
			return $s7;
		case 24:
			return $t8;
		case 25:
			return $t9;
		case 26:
			return $k0;
		case 27:
			return $k1;
		case 28:
			return $gp;
		case 29:
			return $sp;
		case 30:
			return $fp;
		case 31:
			return $ra;
		default:
			printf("Opcao invalida!");
	}
	return 0;
}

// Cria a intrucao em 32 bits e armazena no endereco apontado pelo pc
// Mascara para manter a posicao correta dos 32 bits
int criaInstrucaoR(struct Instrucao *i, int *pc){
	*pc = (((i->opcode)<<26)&0xfc000000)|(((i->rs)<<21))&0x03e00000|(((i->rt)<<16)&0x001f0000)|(((i->rd)<<11)&0x0000f800)|(((i->shamt)<<6)&0x000007c0)|((i->funct)&0x0000003f);
	printf("  Instrucao na memoria: 0x%x\n", *pc);
	return 0;	
}

//cria instrução I e armazena na memória apontada por program counter
int criaInstrucaoI(struct Instrucao *i, int *pc){
	*pc    = (((i->opcode)<<26)&0xfc000000)|(((i->rs)<<21)&0x03e00000)|(((i->rt)<<16)&0x001f0000)|((i->enderecoImediato)&0x0000ffff);
	printf( "rs: %d, rt: %d", i->rs, i->rt);
	printf("  Instrução na memória: 0x%x\n", *pc);
	return 0;
}

//cria instrução J e armazena na memória apontada por program counter
int criaInstrucaoJ(struct Instrucao *i, int *pc){
	*pc    = (((i->opcode)<<26)&0xfc000000)|((i->enderecoDestino)&0x03ffffff);
	printf("  Instrução na memória: 0x%x\n", *pc);
	return 0;	
}

char* decodificaComando(int comando, char* retorno){

	switch(comando){
		case ADD:
			strcpy(retorno,"ADD");
			break;
		case SUB:
			strcpy(retorno,"SUB");
			break;
		case OR:
			strcpy(retorno,"OR");
			break;
		case AND:
			strcpy(retorno,"AND");	
			break;
		case SLT:
			strcpy(retorno,"SLT");
			break;
		case BNE:
			strcpy(retorno,"BNE");
			break;
		case BEQ:
			strcpy(retorno,"BEQ");
			break;
		case J:
			strcpy(retorno,"J");
			break;
		case JR:
			strcpy(retorno,"JR");
			break;
		case LW:
			strcpy(retorno,"LW");
			break;
		case SW:
			strcpy(retorno,"SW");
			break;
		default:
			printf("Opcao invalida!");
			strcpy(retorno, "INV");
		}	
}

void decodificaRegistrador(int registro, char* retorno){
	switch(registro){
		case $zero:
			strcpy(retorno,"$zero");
			break;
		case $at:
			strcpy(retorno,"$at");
			break;
		case $v0:
			strcpy(retorno,"$v0");
			break;
		case $v1:
			strcpy(retorno,"$v1");
			break;
		case $a0:
			strcpy(retorno,"$a0");
			break;
		case $a1:
			strcpy(retorno,"$a1");
			break;
		case $a2:
			strcpy(retorno,"$a2");
			break;
		case $a3:
			strcpy(retorno,"$a3");
			break;
		case $t0:
			strcpy(retorno,"$t0");
			break;
		case $t1:
			strcpy(retorno,"$t1");
			break;
		case $t2:
			strcpy(retorno,"$t2");
			break;
		case $t3:
			strcpy(retorno,"$t3");
			break;
		case $t4:
			strcpy(retorno,"$t4");
			break;
		case $t5:
			strcpy(retorno,"$t5");
			break;
		case $t6:
			strcpy(retorno,"$t6");
			break;
		case $t7:
			strcpy(retorno,"$t7");
			break;
		case $s0:
			strcpy(retorno,"$s0");
			break;
		case $s1:
			strcpy(retorno,"$s1");
			break;
		case $s2:
			strcpy(retorno,"$s2");
			break;
		case $s3:
			strcpy(retorno,"$s3");
			break;
		case $s4:
			strcpy(retorno,"$s4");
			break;
		case $s5:
			strcpy(retorno,"$s5");
			break;
		case $s6:
			strcpy(retorno,"$s6");
			break;
		case $s7:
			strcpy(retorno,"$s7");
			break;
		case $t8:
			strcpy(retorno,"$t8");
			break;
		case $t9:
			strcpy(retorno,"$t9");
			break;
		case $k0:
			strcpy(retorno,"$k0");
			break;
		case $k1:
			strcpy(retorno,"$k1");
			break;
		case $gp:
			strcpy(retorno,"$gp");
			break;
		case $sp:
			strcpy(retorno,"$sp");
			break;
		case $fp:
			strcpy(retorno,"$fp");
			break;
		case $ra:
			strcpy(retorno,"$ra");
			break;
		default:
			printf("Opcao invalida!");
			strcpy(retorno,"INV");
	}
}

// Carrega uma instrucao no endereco do program counter (pc)
int carregaInstrucao(int *pc){

	int formato, op, rs, rt, rd, sh, funct;
    int endInstrucao, endDestino;

	struct Instrucao *ins = (struct Instrucao*)malloc(sizeof(struct Instrucao));

	printf("  ====================\n");
	printf("  Formato da instrucao\n");
	printf("  ====================\n");
	printf("  1. formato R\n");
	printf("  2. formato I\n");
	printf("  3. formato J\n");
	printf("  Digite o formato da instrucao: ");
	scanf("%d", &formato);

	switch(formato){
		case 1:
			op = 0;
			funct = selecionaOpcode();
			printf("  =============\n");
			printf("  Selecao de RS\n");
			printf("  =============\n");
			rs = selecionaRegistrador();
			printf("  =============\n");
			printf("  Selecao de RT\n");
			printf("  =============\n");
			rt = selecionaRegistrador();
			printf("  =============\n");
			printf("  Selecao de RD\n ");
			printf("  =============\n");
			rd = selecionaRegistrador();
			sh = 0;
			ins->opcode = op;
			ins->rs = rs;
			ins->rt = rt;
			ins->rd = rd;
			ins->shamt = sh;
			ins->funct = funct;
			criaInstrucaoR(ins, pc);
			break;
		case 2:
			op = selecionaOpcode();
			printf("  =============\n");
			printf("  Selecao de RS\n");
			printf("  =============\n");
			rs = selecionaRegistrador();
			printf("  =============\n");
			printf("  Selecao de RT\n");
			printf("  =============\n");
			rt = selecionaRegistrador();
			printf("  ==================\n");
			printf("  Endereco imediato\n ");
			printf("  ==================\n");
			printf("  Entre com o endereco/imediato (16 bits): ");
			scanf("%d", endInstrucao);
			ins->opcode = op;
			ins->rs = rs;
			ins->rt = rt;
			ins->enderecoImediato = endInstrucao;
			criaInstrucaoI(ins, pc);
			break;
		case 3:
			op = selecionaOpcode();
			printf("  ==================\n");
			printf("  Endereco de Destino\n ");
			printf("  ==================\n");
			printf("Entre com o endereco de destino (26 bits): ");
			scanf("%d", &endDestino);
			ins->opcode = op;
			ins->enderecoDestino = endDestino;
			criaInstrucaoJ(ins, pc);
			break;
		default:
			printf("  Opcao de formato invalido!");
	}
	free(ins);
	printf("  Instrucao carregada na memoria apontada por program counter (pc): 0x%x\n", pc);
	return 0;
};

// le a instrucao apontada pelo program counter (pc)
int leInstrucao(int *pc, struct Instrucao *i){
	
	// Endereco do program counter
	printf("  O endereco do program counter e: 0x%x\n", pc);
	
	// ler opcode
	i->opcode = ((*pc)>>26)&0x3f;
	if (i->opcode == 0){
		printf("  Instrucao no formato R\n");
		printf("  opcode: %d\n", i->opcode);
		// Desloca 21 bits para direita para poder ler rs, usa (&) com a mascara para 5 bits
		i->rs = ((*pc)>>21)&0x0000001f;
		printf("  rs: %d\n", i->rs);
		// Desloca 16 bits para direita para poder ler rt, usa (&) com a mascara para 5 bits
		i->rt = ((*pc)>>16)&0x0000001f;
		printf("  rt: %d\n", i->rt);
		// Desloca 11 bits para direita para poder ler rd, usa (&) com a mascara para 5 bits
		i->rd = ((*pc)>>11)&0x0000001f;
		printf("  rd: %d\n", i->rd);
		// Desloca 6 bits para direita para poder ler shamt, usa (&) com a mascara para 5 bits
		i->shamt = ((*pc)>>6&0x0000001f);
		printf("  shamt: %d\n", i->shamt);
		// Le funct e usa AND(&) com a mascara para 6 bits
		i->funct = (*pc)&0x0000003f;
		printf("  funct: %d\n", i->funct);
	} else if (i->opcode == 2){
		printf("  Instrucao no formato J\n");
		printf("  opcode: %d\n", i->opcode);
		// ler endere�o destino
		i->enderecoDestino = (*pc)&0x3ffffff; // (mascara), le 26 bits
		printf("  endereco destino: %d\n", i->enderecoDestino);
	} else {
		printf("  Instrucao no formato I\n");
		printf("  opcode: %d\n", i->opcode);
		// Ler rs
		i->rs = ((*pc)>>21)&0x0000001f; // (mascara), le 5 bits
		printf("  rs: %d\n", i->rs);
		// Ler rt
		i->rt = ((*pc)>>16)&0x0000001f; // (mascara), le 5 bits
		printf("  rt: %d\n", i->rt);
		// Ler endereco/imediato
		i->enderecoImediato = (*pc)&0x0000ffff; // (mascara), le 16 bits
		printf("  endereco imediato: %d\n", i->enderecoImediato);
	}
	return 0;
};

// Decodifica a instrucao
int decodificaInstrucao(struct Instrucao *i){
	char* comando = (char*)malloc(3*sizeof(char));
	char* rs = (char*)malloc(5*sizeof(char));
	char* rt = (char*)malloc(5*sizeof(char));
	char* rd = (char*)malloc(5*sizeof(char));
	if (i->opcode == 0){
		printf("  Formato da instrucao: R\n");
		decodificaComando(i->funct, comando);
		decodificaRegistrador(i->rs, rs);
		decodificaRegistrador(i->rt, rt);
		decodificaRegistrador(i->rd, rd);
		printf("  Instrucao: %s %s %s %s\n", comando, rd, rs, rt);
	} else if(i->opcode == 2){
		printf("  Formato da instrucao: J\n");
		decodificaComando(i->opcode, comando);
		printf("  Instrucao: %s %d\n", comando, i->enderecoDestino);
	} else{
		printf("  Formato da instrucao: I\n");
		decodificaComando(i->opcode, comando);
		decodificaRegistrador(i->rs, rs);
		decodificaRegistrador(i->rt, rt);
		printf("  Instrucao: %s %s %s %d\n", comando, rs, rt, i->enderecoImediato);
	}
	free(comando);
	free(rs);
	free(rt);
	free(rd);
	return 0;
};

int executaInstrucao(struct Instrucao *i){

	int rs, rt, rd;
	char* rs_type = (char*)malloc(5*sizeof(char));
	char* rt_type = (char*)malloc(5*sizeof(char));
	char* rd_type = (char*)malloc(5*sizeof(char));

	decodificaRegistrador(i->rs, rs_type);
	decodificaRegistrador(i->rt, rt_type);
	decodificaRegistrador(i->rd, rd_type);

	printf("  Escreva o valor do registrador RS (%s): ",rs_type);
	scanf("%d", &rs);
	printf("  Escreva o valor do registrador RT (%s): ",rt_type);
	scanf("%d", &rt);
	rd = rs + rt;
	printf("  O valor do resultado no registrador RD (%s) e: %d\n", rd_type, rd);

	free(rd_type);
	free(rs_type);
	free(rt_type);
	return 0;
}

int main(){

	int opcao = 0;										                       // opcao de menu 
	int *pc = (int*)malloc(sizeof(int));  			                           // program counter
	struct Instrucao *i = (struct Instrucao*)malloc(sizeof(struct Instrucao)); // instrucao MISP

	while(opcao != 6){
		printf("===============================================\n");
		printf("                MIPS SIMULATOR                 \n");
		printf("===============================================\n");
		printf(" \n");
		printf("  MENU\n");
		printf("  ----\n");
		printf("  1. Carregar instrucao MIPS\n");
		printf("  2. Ler instrucao MIPS\n");
		printf("  3. Decodificar instrucao MIPS\n");
		printf("  4. Executar instrucao (somente instrucao ADD formato R)\n");
		printf("  5. Ler valor do program counter(pc)\n");
		printf("  6. Sair\n");
		printf("  \n");
		printf("  Escolha uma opcao: ");
		scanf("%d", &opcao);
		switch(opcao){
			case 1:
				// carrega instrucao na memoria (pc - program counter)
				carregaInstrucao(pc);
				break;
			case 2:
				// le a instrucao da memoria apontada pelo pc	
				leInstrucao(pc, i);
				break;
			case 3:
				// decodifica a instrucao MIPS
				decodificaInstrucao(i);
				break;
			case 4:
				// executa instrucao (somente ADD)
				executaInstrucao(i);
				pc++; // vai para a proxima posicao da proxima instrucao
				break;
			case 5:
				// le valor do program counter
				if (pc != NULL){
					printf("  O valor do program counter e: 0x%x\n", pc);
				}else{
					printf("  O valor do program counter e invalido!\n");
				}
				break;
			case 6:
				// opcao de saida
				printf("  Saindo do MISP Simulator...\n");
				break;
			default:
				printf("  Opcao invalida!\n");
		}
		system("pause"); // para o programa
	}
	free(pc);
	free(i);
	return 0;	
}