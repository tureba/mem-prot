/* Exemplo de servidor vulneravel a stack overflow e format string */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>

#define   MAX    2048
#define   PORTA  8123   // porta a ser usada pelo servidor
#define MAXCON 5   // maximo de conexoes simultaneas
#define   ERRO  -1
#define   MSG    "UNIX rfdslabs.com.br version 4.5v build-1985\nlogin: "

void espera_cliente(int sockfd);
void cria_conexao(void);
void autoriza_login(char *login);

int main(void)
{
   cria_conexao();
}

void espera_cliente(int sockfd)
{
   char bufferleitura[MAX];
   struct sockaddr_in rede;
   int cliente, resposta, tamanho;

   tamanho = sizeof(rede);
   memset(bufferleitura, 0x00, sizeof(bufferleitura));
   
   printf("Esperando conexao...\n");

   if((cliente = accept(sockfd, (struct sockaddr *)&rede, &tamanho)) == ERRO)
   {
      fprintf(stderr, "Erro: %s\n", strerror(errno));
      shutdown(sockfd, SHUT_RDWR);
      close(sockfd);
      exit(ERRO);
   }

   fprintf(stdout, "Conexao recebida de %s\n", inet_ntoa(rede.sin_addr));
   write(cliente, MSG, strlen(MSG)); // envia mensagem para o cliente
   resposta = read(cliente, bufferleitura, sizeof(bufferleitura));
   autoriza_login(bufferleitura);
}

void cria_conexao(void)
{
   struct sockaddr_in conexao;
   int sockfd, opt;

   opt = 1;

   if((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == ERRO)
   {
      fprintf(stderr, "Erro de socket: %s\n", strerror(errno));
      exit(ERRO);
   }

   if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
   {
      fprintf(stderr, "Erro setsockopt(): %s\n", strerror(errno));
      exit(ERRO);
   }
   
   /* preenchendo as estruturas de rede */
   conexao.sin_family = AF_INET;
   conexao.sin_port = htons(PORTA);
   conexao.sin_addr.s_addr = INADDR_ANY;

   if(bind(sockfd, (struct sockaddr *)&conexao, sizeof(struct sockaddr)) == ERRO)
   {
      fprintf(stderr, "Erro em bind(): %s\n", strerror(errno));
      exit(ERRO);
   }

   listen(sockfd, MAXCON);
   espera_cliente(sockfd);
   close(sockfd);
   exit(0);
}

void autoriza_login(char *login)
{
   char autorizacao[256];
   char armazenado[32];
   
   memset(autorizacao, 0x00, sizeof(autorizacao));
   fprintf(stdout, "Autorizando usuario...\n");
   // O BUG DE FORMAT STRING ESTA' AQUI EMBAIXO!
   snprintf(armazenado, sizeof(armazenado), login);
   // O BUG DE STACK OVERFLOW ESTA' AQUI EMBAIXO!
   strcpy(autorizacao, login);
   fprintf(stdout, "Armazenando o login do usuario...\n");
   fprintf(stdout, "OK! Autorizado o usuario %s", armazenado);
}

