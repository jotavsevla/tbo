# TBO - Técnica de Busca e Ordenação

Repositório contendo implementações de estruturas de dados e algoritmos desenvolvidos para a disciplina de Técnica de Busca e Ordenação (TBO).

## Estrutura do Repositório

```
tbo/
├── ProjetoI/          # Sistema de gerenciamento de cinemas e filmes
├── ProjetoII/         # Busca em dicionário com corretor ortográfico
├── TrabalhoI/         # Implementações de listas
├── TrabalhoII/        # Comparação de algoritmos de ordenação
└── Truco/            # Projeto adicional
```

---

## ProjetoI - Sistema de Gerenciamento de Cinemas e Filmes

Sistema completo para busca e filtragem de filmes e cinemas utilizando estruturas de dados avançadas.

### Características

- **Estruturas de dados implementadas:**
  - Árvore Rubro-Negra (Red-Black Tree) para busca eficiente por ano
  - Tabela Hash para acesso rápido
  - Sistema de triagem de filmes

- **Funcionalidades:**
  - Busca de filmes por:
    - Tipo (movie, short, tvSeries, etc.)
    - Gênero (Action, Drama, Comedy, etc.)
    - Duração (intervalo min/max em minutos)
    - Ano de lançamento (ano específico ou intervalo)
  - Busca de cinemas por:
    - Distância (coordenadas X, Y)
    - Preço do ingresso
  - Sistema de filtros combinados

### Arquivos principais

- `main.cpp`: Ponto de entrada do programa
- `Classes/Menu.h`: Interface de menu para interação com o usuário
- `Classes/Arquivo.h`: Carregamento e gerenciamento de dados
- `Classes/RedBlackTree.h`: Implementação da árvore rubro-negra
- `Classes/TabelaHash.h`: Implementação da tabela hash
- `Classes/Triagem.h`: Sistema de triagem e filtragem
- `Classes/Filme.h`: Classe para representar filmes
- `Classes/Cinema.h`: Classe para representar cinemas
- `Classes/Busca.h`: Algoritmos de busca

### Formato dos dados

**Cinemas (cinemas.txt):**

```
Cinema_ID, Nome_do_Cinema, Coordenada_X, Coordenada_Y, Preço_Ingresso, Filmes_Em_Exibição
cc00001, Cineplex Estrela, 347865, 478921, 12.50, tt8000001, tt8000023, tt8000056
```

**Filmes (filmes.txt):**
Arquivo grande (~47MB) contendo informações detalhadas de filmes.

### Como compilar e executar

```bash
cd ProjetoI
mkdir build && cd build
cmake ..
make
./ProjetoI
```

---

## ProjetoII - Busca em Dicionário com Corretor Ortográfico

Sistema de busca em dicionário português com suporte a wildcards e correção ortográfica inteligente.

### Características

- **Algoritmos implementados:**
  - KMP (Knuth-Morris-Pratt) para busca de padrões
  - KMP com suporte a wildcards (\*)
  - Distância de Levenshtein para similaridade de palavras
  - Algoritmos de correção ortográfica específicos para português

- **Funcionalidades:**
  1. **Busca no dicionário:**
     - Busca exata
     - Busca com wildcards (ex: "c\*sa" encontra "casa", "coisa", etc.)

  2. **Sugestões para palavras incorretas:**
     - Palavras similares por distância de Levenshtein (até 2 diferenças)
     - Correção R/S adicional ou substituído
     - Correção SC adicional (ex: "sena" → "cena", "acender" → "ascender")
     - Correção M antes de P/B (ex: "enprego" → "emprego")

### Algoritmos de correção ortográfica

1. **Levenshtein Distance**: Encontra palavras com até 2 operações de diferença (inserção, remoção, substituição)
2. **R/S Adicional**: Corrige erros com letras R e S faltantes ou extras
3. **SC Adicional**: Identifica e corrige usos de 'sc' na língua portuguesa
4. **M antes de P/B**: Aplica a regra ortográfica "usa-se M antes de P e B"

### Como compilar e executar

```bash
cd ProjetoII
g++ -std=c++11 main.cpp -o dicionario
./dicionario
```

### Exemplo de uso

```
Escolha o modo de busca:
1 - Buscar palavra no dicionário
2 - Buscar sugestões para palavras erradas
S - Sair
> 1

Informe o padrão a ser buscado: c*sa
Padrão encontrado na posição: 123456 | Palavra completa: casa
Padrão encontrado na posição: 234567 | Palavra completa: coisa
```

---

## TrabalhoI - Implementações de Listas

Três implementações diferentes de listas para estudo comparativo de estruturas de dados.

### Estruturas implementadas

#### 1. Lista Física (listafisica/)

- Implementação com alocação estática
- Usa array de tamanho fixo
- Classes:
  - `StaticLista.h`: Lista com array estático

#### 2. Lista Ligada (listaligada/)

- Implementação com encadeamento simples
- Alocação dinâmica de nós
- Classes:
  - `ListaLigada.h`: Lista encadeada simples
  - `Nodo.h`: Nó da lista

#### 3. Lista Duplamente Ligada (listaduploligada/)

- Implementação com encadeamento duplo
- Permite navegação bidirecional
- Classes:
  - `ListaLigada.h`: Lista duplamente encadeada
  - `Nodo.h`: Nó com ponteiro anterior e próximo

### Comparação de implementações

| Característica  | Lista Física | Lista Ligada | Lista Dupla |
| --------------- | ------------ | ------------ | ----------- |
| Alocação        | Estática     | Dinâmica     | Dinâmica    |
| Acesso          | O(1)         | O(n)         | O(n)        |
| Inserção início | O(n)         | O(1)         | O(1)        |
| Inserção fim    | O(1)         | O(n)         | O(1)\*      |
| Remoção         | O(n)         | O(n)         | O(1)\*\*    |
| Memória         | Fixa         | Variável     | Variável    |

\* Com ponteiro para o último elemento
\*\* Quando se tem referência ao nó

### Como compilar e executar

```bash
# Lista Física
cd TrabalhoI/listafisica
g++ -std=c++11 main.cpp classes/*.cpp -o listafisica
./listafisica < in1.txt

# Lista Ligada
cd TrabalhoI/listaligada
g++ -std=c++11 main.cpp classes/*.cpp -o listaligada
./listaligada

# Lista Duplamente Ligada
cd TrabalhoI/listaduploligada
g++ -std=c++11 main.cpp classes/*.cpp -o listaduploligada
./listaduploligada
```

---

## TrabalhoII - Comparação de Algoritmos de Ordenação

Análise experimental comparando Insertion Sort e Selection Sort através de contagem de acessos à memória.

### Características

- **Algoritmos implementados:**
  - Insertion Sort
  - Selection Sort

- **Metodologia:**
  - Testa listas de tamanho 1 a 100
  - Gera números aleatórios entre 1 e 1000
  - Conta acessos à memória (leituras e escritas)
  - Visualiza resultados em gráfico

### Análise de complexidade

| Algoritmo      | Melhor Caso | Caso Médio | Pior Caso | Estável |
| -------------- | ----------- | ---------- | --------- | ------- |
| Insertion Sort | O(n)        | O(n²)      | O(n²)     | Sim     |
| Selection Sort | O(n²)       | O(n²)      | O(n²)     | Não     |

### Contagem de acessos

O programa conta:

- Cada comparação entre elementos
- Cada operação de swap (3 acessos: leitura de 2 elementos + escrita de 1)

### Visualização

Gera um gráfico comparativo usando matplotlib mostrando:

- Eixo X: Tamanho da lista (1-100)
- Eixo Y: Número de acessos à memória
- Duas curvas: Insertion Sort vs Selection Sort

### Como compilar e executar

```bash
cd TrabalhoII
g++ -std=c++11 main.cpp -o sorting
./sorting
```

O programa irá:

1. Executar Insertion Sort para listas de 1 a 100 elementos
2. Executar Selection Sort para listas de 1 a 100 elementos
3. Salvar os dados em `data_of_chart.txt`
4. Executar automaticamente `python3 main.py` para gerar o gráfico

### Requisitos

- C++ compiler com suporte a C++11
- Python 3
- matplotlib
- numpy

Instalar dependências Python:

```bash
pip install matplotlib numpy
```

---

## Estruturas de Dados Utilizadas no Repositório

### Árvore Rubro-Negra (Red-Black Tree)

- **Projeto:** ProjetoI
- **Uso:** Indexação de filmes por ano
- **Complexidade:** O(log n) para inserção, busca e remoção
- **Características:** Auto-balanceamento, garantia de altura logarítmica

### Tabela Hash

- **Projeto:** ProjetoI
- **Uso:** Acesso rápido a dados de filmes e cinemas
- **Complexidade:** O(1) médio para inserção e busca

### Lista Estática (Array)

- **Projeto:** TrabalhoI
- **Uso:** Implementação básica de lista
- **Complexidade:** O(1) para acesso, O(n) para inserção/remoção

### Lista Ligada Simples

- **Projeto:** TrabalhoI
- **Uso:** Lista com encadeamento simples
- **Complexidade:** O(1) para inserção no início, O(n) para busca

### Lista Duplamente Ligada

- **Projeto:** TrabalhoI
- **Uso:** Lista com encadeamento bidirecional
- **Complexidade:** O(1) para inserção/remoção (com referência), O(n) para busca

---

## Algoritmos Implementados

### Algoritmos de Busca

#### KMP (Knuth-Morris-Pratt)

- **Projeto:** ProjetoII
- **Arquivo:** `ProjetoII/main.cpp`
- **Complexidade:** O(n + m)
- **Uso:** Busca de padrões em texto
- **Características:** Pré-processa o padrão para evitar comparações redundantes

#### KMP com Wildcards

- **Projeto:** ProjetoII
- **Arquivo:** `ProjetoII/main.cpp`
- **Complexidade:** O(n × m)
- **Uso:** Busca com caracteres curinga (\*)

### Algoritmos de Ordenação

#### Insertion Sort

- **Projeto:** TrabalhoII
- **Arquivo:** `TrabalhoII/main.cpp:49`
- **Complexidade:**
  - Melhor caso: O(n)
  - Pior caso: O(n²)
- **Estável:** Sim
- **In-place:** Sim

#### Selection Sort

- **Projeto:** TrabalhoII
- **Arquivo:** `TrabalhoII/main.cpp:65`
- **Complexidade:** O(n²) em todos os casos
- **Estável:** Não
- **In-place:** Sim

### Algoritmos de Similaridade

#### Distância de Levenshtein

- **Projeto:** ProjetoII
- **Arquivo:** `ProjetoII/main.cpp:245`
- **Complexidade:** O(n × m)
- **Uso:** Calcular distância de edição entre duas strings
- **Aplicação:** Corretor ortográfico, sugestões de palavras

---

## Tecnologias Utilizadas

- **Linguagem:** C++ (C++11 ou superior)
- **Visualização:** Python 3 com matplotlib e numpy
- **Build System:** CMake (ProjetoI)
- **Compilador:** g++ / clang++

---

## Como Usar Este Repositório

### Clonar o repositório

```bash
git clone <url-do-repositorio>
cd tbo
```

### Navegar pelos projetos

Cada diretório (ProjetoI, ProjetoII, TrabalhoI, TrabalhoII) é independente e contém seu próprio código e instruções.

### Compilar projetos individuais

Consulte a seção específica de cada projeto acima para instruções de compilação.

---

## Conceitos Aprendidos

### Estruturas de Dados

- Árvores balanceadas (Red-Black Tree)
- Tabelas hash e funções de dispersão
- Listas estáticas, ligadas e duplamente ligadas
- Trade-offs entre diferentes implementações

### Algoritmos

- Busca de padrões (KMP)
- Algoritmos de ordenação e análise de complexidade
- Algoritmos de similaridade de strings
- Otimização e análise experimental

### Boas Práticas

- Separação de responsabilidades (classes separadas)
- Encapsulamento e modularização
- Análise de complexidade assintótica
- Validação experimental de complexidade teórica

---

## Autor

Desenvolvido como parte da disciplina de Técnica de Busca e Ordenação.

## Licença

Projeto acadêmico - Material de estudo.
