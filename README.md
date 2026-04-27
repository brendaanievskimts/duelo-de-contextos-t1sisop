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

# Analise de Corrupção(FALTANDO FAZER)
Ao analisarmos os valores de 
---

# Grafico de Escalabilidade

  Para demonstrar a escalabilidade por meio de um gráfico, utilizamos o Google Sheets. Ao analisarmos os dados, é possível perceber que o tempo de execução diminui à medida que o número de workers aumenta; essa diferença é mais perceptível de 2 para 4. Nos demais casos, os ganhos são menos significativos, revelando o limite da escalabilidade. Ao compararmos threads e processos, notamos que seus comportamentos são bem semelhantes, apresentando apenas algumas variações no desempenho.

<img width="927" height="421" alt="image" src="https://github.com/user-attachments/assets/95d420a7-f844-40c1-9211-24757f83bdc4" />
(Comparação de tempo de execução via Google Sheets.)


# Conclusão(FALTANDO FAZER)
