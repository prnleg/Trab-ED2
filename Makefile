Run: main.c       
	@gcc -lm -o $@ $<

Teste1: main.c # Teste de load de 10 dados.
	@printf "Caso 1, Load de 10 dados\n"
	@gcc -lm -o $@ $<
	@echo 1 | ./$@
  
Teste2: main.c # Teste de load de 100 dados.
	@printf "Caso 2, Load de 100 dados\n"
	@gcc -lm -o $@ $<
	@echo 2 | ./$@
 
Teste3: main.c # Teste de load de 500 dados.
	@printf "Caso 3, Load de 500 dados\n"
	@gcc -lm -o $@ $<
	@echo 3 | ./$@  

Teste4: main.c # Teste de load de 1000 dados.
	@printf "Caso 4, Load de 1000 dados\n"
	@gcc -lm -o $@ $<
	@echo 4 | ./$@  

Teste5: main.c # Teste de load de 1500 dados.
	@printf "Caso 5, Load de 1500 dados\n"
	@gcc -lm -o $@ $<
	@echo 5 | ./$@

Teste6: main.c # Mostar exemplo de N acessos
	@printf "Caso 6 Exemplo de N acessos\n"
	@gcc -lm -o $@ $<
	@echo 6 100 | ./$@

Teste7: main.c # Exemplo de N dados armazenados.
	@printf "Caso 7 Exemplo de N dados\n"
	@gcc -lm -o $@ $<
	@echo 7 20| ./$@  
 
Teste8: main.c #  Demonstração de um dado especifico.
	@printf "Caso 1, Amostra de uma linha de dados.\n"
	@gcc -lm -o $@ $<
	@echo 8 | ./$@

TesteTodos: Teste1 Teste2 Teste3 Teste4 Teste5 Teste6 Teste7 Teste8
  