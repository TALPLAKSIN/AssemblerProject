OBJS = assembler.o AddressingMethods.o CommendAndInstructions.o convertAddress.o convertInstructions.o definitionOfRegAndOperation.o encodeAndWriteToFile.o FileMethod.o HandelLable.o McrList.o OpenMcr.o OperationLine.o TagList.o ValidFile.o writeInBaseFour.o
ASSEMBLER_FILES = *.ob *.ext *.ent *.o

assembler: $(OBJS)
	gcc -g -ansi -Wall -pedantic $(OBJS) -o assembler

assembler.o: assembler.c
	gcc -g -c -ansi -Wall -pedantic assembler.c -o assembler.o

AddressingMethods.o: AddressingMethods.c AddressingMethods.h
	gcc -g -c -ansi -Wall -pedantic AddressingMethods.c -o AddressingMethods.o

CommendAndInstructions.o: CommendAndInstructions.c CommendAndInstructions.h
	gcc -g -c -ansi -Wall -pedantic CommendAndInstructions.c -o CommendAndInstructions.o

convertAddress.o: convertAddress.c convertAddress.h
	gcc -g -c -ansi -Wall -pedantic convertAddress.c -o convertAddress.o

convertInstructions.o: convertInstructions.c convertInstructions.h
	gcc -g -c -ansi -Wall -pedantic convertInstructions.c -o convertInstructions.o

definitionOfRegAndOperation.o: definitionOfRegAndOperation.c definitionOfRegAndOperation.h
	gcc -g -c -ansi -Wall -pedantic definitionOfRegAndOperation.c -o definitionOfRegAndOperation.o

encodeAndWriteToFile.o: encodeAndWriteToFile.c encodeAndWriteToFile.h
	gcc -g -c -ansi -Wall -pedantic encodeAndWriteToFile.c -o encodeAndWriteToFile.o

FileMethod.o: FileMethod.c FileMethod.h
	gcc -g -c -ansi -Wall -pedantic FileMethod.c -o FileMethod.o

HandelLable.o: HandelLable.c HandelLable.h
	gcc -g -c -ansi -Wall -pedantic HandelLable.c -o HandelLable.o

McrList.o: McrList.c McrList.h
	gcc -g -c -ansi -Wall -pedantic McrList.c -o McrList.o

OpenMcr.o: OpenMcr.c OpenMcr.h
	gcc -g -c -ansi -Wall -pedantic OpenMcr.c -o OpenMcr.o

OperationLine.o: OperationLine.c OperationLine.h
	gcc -g -c -ansi -Wall -pedantic OperationLine.c -o OperationLine.o

TagList.o: TagList.c TagList.h
	gcc -g -c -ansi -Wall -pedantic TagList.c -o TagList.o

ValidFile.o: ValidFile.c ValidFile.h
	gcc -g -c -ansi -Wall -pedantic ValidFile.c -o ValidFile.o

writeInBaseFour.o: writeInBaseFour.c writeInBaseFour.h
	gcc -g -c -ansi -Wall -pedantic writeInBaseFour.c -o writeInBaseFour.o

clean:
	rm -f $(OBJS) $(ASSEMBLER_FILES) assembler
