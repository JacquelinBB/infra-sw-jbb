# infra-sw-jbb
Exercícios da cadeira de infraestrutura de software
Atividade de número: 6

Como clonar o repositório:
$ git clone 
$ cd infra_software_tutoria6

Como utilizar o programa:
Existe um arquivo makefile, nele tem os comandos run e clean, para compilar você usa o "make" e em seguida "make run" para rodar o programa. 

Sobrea a atividade:
O programa tem 2 grupos de threads, que respectivamente é o produtor e consumidor, que utiliza um buffer circular.

O grupo de produção executam uma função e retornam um valor para o Buffer e lá o segundo grupo atua varendo o buffer e recolhendo os valores criados.
