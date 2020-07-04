`ExampleTypes.vcxproj` contém uma base de projeto pra buildar um .idl

`ExampleClient.vcxproj` contém uma base de projeto para buildar um client

Obs: Só tem que renomear as ocorrências de ExampleClient (e exempleclient); Se cada projeto estiver em uma pasta, é preciso botar o path para a pasta do .idl nas dependências dos clients; Na pasta exemple tem o exemplo da temperatura, só tem que criar uma solução no VS e adicionar os três .vcxproj