# Catálogo de Livros

Sistema que cadastra livros e os ordena por **nome** ou **preço**, em ordem
**crescente** ou **decrescente**.

- **Backend (algoritmo):** C — `livro.c`, `livro.h`, `main.c`. A ordenação é um bubble sort sobre uma cópia do vetor de livros.
- **Frontend (duas versões):**
  - Web: `index.html` + `servidor.py` (abre no navegador, funciona também no Codespaces).
  - Desktop: Python + Tkinter — `interface.py`.
- **Ponte entre os dois:** `ponte_c.py`. A interface manda comandos de texto para o programa em C e mostra a lista que ele devolve já ordenada.

```
Versão web:      index.html  ->  servidor.py  ->  ponte_c.py  ->  catalogo (C)
Versão desktop:  interface.py  ->  ponte_c.py  ->  catalogo (C)
```

## Como rodar

1. Compilar o C (na pasta do projeto):

   ```
   gcc main.c livro.c -o catalogo
   ```

2. Abrir a interface, escolhendo uma das versões:

   **Web (navegador)**

   ```
   python3 servidor.py
   ```

   (no Windows: `python servidor.py`). Depois abra `http://localhost:8000` no navegador.
   No Codespaces, abra o endereço pela aba **Ports** (ícone de globo ao lado da porta 8000).

   **Desktop (Tkinter)**

   ```
   python interface.py
   ```

   (no Windows, se `python` não funcionar, use `py interface.py`). O Tkinter já vem na
   instalação padrão do Python no Windows. No Linux: `sudo apt install python3-tk`.
   A versão desktop não abre no Codespaces, que não tem tela.

## Modo terminal (sem interface)

O menu original continua funcionando:

```
./catalogo
```

## Protocolo entre a interface e o C

| A janela envia | O C responde |
|---|---|
| `CADASTRAR;nome;preco` | `OK;total` ou `ERRO;motivo` |
| `ORDENAR;nome\|preco;crescente\|decrescente` | uma linha `nome;preco` por livro, e depois `FIM` |
| `SAIR` | encerra o programa |

## Integrantes

- (nomes da equipe)
