# T1 - Duelo de Contextos (Processos vs Threads)

# Integrantes do Grupo

- Brenda Anievski  
- Brenda Brizola  
- Cecilia Ricalcati

---

# Como compilar e executar

1. Certifique-se de que o GCC está instalado no seu sistema.
2. Execute `make` para compilar o programa.
3. Execute os experimentos (usando time para verificar o tempo de execução):

```bash
time ./threads 2
time ./threads 4
time ./threads 8

time ./processos 2
time ./processos 4
time ./processos 8
```
---

## Limpeza

Execute `make clean` para remover arquivos objeto e o executável.

---

# Assinatura do Hardware

Comando executado:

```bash
sysctl -a | grep hw.ncpu
```

Resultado:

```bash
hw.ncpu: 8
```
---

# Resultados das execuções no MacOS

## Threads

### 2 Threads (`time ./threads 2`)

```text
Executando T1...
T1 contador final: 504255980

Executando T2...
T2 contador final: 1000000000

./threads 2  3,54s user 0,01s system 160% cpu 2,206 total
```

---

### 4 Threads (`time ./threads 4`)

```text
Executando T1...
T1 contador final: 279003512

Executando T2...
T2 contador final: 1000000000

./threads 4  4,15s user 0,01s system 386% cpu 1,077 total
```

---

### 8 Threads (`time ./threads 8`)

```text
Executando T1...
T1 contador final: 227918096

Executando T2...
T2 contador final: 1000000000

./threads 8  6,06s user 0,03s system 606% cpu 1,004 total
```

---

## Processos

### 2 Processos (`time ./processos 2`)

```text
Executando P1...
P1 contador final: 503293739

Executando P2...
P2 contador final: 1000000000

./processos 2  3,49s user 0,01s system 161% cpu 2,164 total
```

---

### 4 Processos (`time ./processos 4`)

```text
Executando P1...
P1 contador final: 279628453

Executando P2...
P2 contador final: 1000000000

./processos 4  4,23s user 0,02s system 381% cpu 1,115 total
```

---

### 8 Processos (`time ./processos 8`)

```text
Executando P1...
P1 contador final: 228547175

Executando P2...
P2 contador final: 1000000000

./processos 8  6,18s user 0,03s system 641% cpu 0,967 total
```

---

# Tabela de Tempos

| N | Threads (s) | Processos (s) |
|---|---|---|
| 2 | 2.206 | 2.164 |
| 4 | 1.077 | 1.115 |
| 8 | 1.004 | 0.967 |

---

# Analise de Corrupção

  Ao analisarmos os valores de T1 e P1, observamos que o valor final do contador ficou abaixo de 1 bilhão em todos os casos, variando de aproximadamente 500 milhões (com 2 workers) até cerca de 228 milhões (com 8 workers). Isso ocorre devido às condições de corrida, pois múltiplas threads ou processos acessam e modificam a mesma variável sem utilizar mecanismos de sincronização. Como a operação de incremento não é atômica, há perda de atualizações durante a execução. Além disso, a utilização de um hardware com 8 núcleos possibilitou uma execução paralela mais efetiva, aumentando a concorrência e, consequentemente, o número de conflitos, o que intensificou a corrupção do valor final do contador.
  
---

# Grafico de Escalabilidade

  Para demonstrar a escalabilidade por meio de um gráfico, utilizamos o Google Sheets. Ao analisarmos os dados, é possível perceber que o tempo de execução diminui à medida que o número de workers aumenta; essa diferença é mais perceptível de 2 para 4. Nos demais casos, os ganhos são menos significativos, revelando o limite da escalabilidade. Ao compararmos threads e processos, notamos que seus comportamentos são bem semelhantes, apresentando apenas algumas variações no desempenho.

<img width="927" height="421" alt="image" src="https://github.com/user-attachments/assets/95d420a7-f844-40c1-9211-24757f83bdc4" />
(Comparação de tempo de execução via Google Sheets.)

---

# Conclusão
  Este trabalho teve como objetivo comparar o comportamento de threads e processos em um contexto de concorrência, analisando tanto a corrupção de dados quanto a escalabilidade em função do número de workers.
  
  Os experimentos confirmaram que, na ausência de mecanismos de sincronização, tanto threads quanto processos sofrem com condições de corrida. O contador de T1 e P1, que deveria atingir 1 bilhão, apresentou valores significativamente menores em todos os cenários - chegando a aproximadamente 228 milhões com 8 workers - evidenciando que o paralelismo real, viabilizado pelos 8 núcleos do hardware utilizado, intensifica os conflitos de acesso à memória compartilhada e agrava a corrupção dos dados.
  
  Em relação à escalabilidade, observou-se que o aumento no número de workers reduz o tempo de execução, porém com retornos decrescentes. O ganho mais expressivo ocorreu ao dobrar os workers de 2 para 4, enquanto a transição de 4 para 8 apresentou melhoria marginal, indicando que o programa se aproxima do limite prático de paralelização - fenômeno previsto pela Lei de Amdahl, dado que parte da execução permanece sequencial.
  
  A comparação entre threads e processos revelou comportamentos bastante similares em termos de tempo de execução e grau de corrupção. As pequenas variações observadas podem ser atribuídas às diferenças nos mecanismos de criação e troca de contexto: processos possuem espaços de endereçamento independentes e maior overhead de criação, enquanto threads compartilham memória e são mais leves. Apesar disso, no cenário testado, essas diferenças não foram suficientes para produzir resultados expressivamente distintos.
  
  Conclui-se que a escolha entre threads e processos deve considerar o contexto da aplicação: threads são mais eficientes em tarefas que exigem compartilhamento de dados, mas exigem atenção redobrada à sincronização para evitar corrupção; processos, por sua vez, oferecem maior isolamento e segurança, sendo mais adequados quando a independência entre as unidades de execução é prioritária.
