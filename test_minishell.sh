#!/bin/bash

# Ruta hacia tu minishell (modifica si está en otro lugar)
MINISHELL=./minishell

# Lista de comandos a probar
declare -a tests=(
    "echo hola"
    "echo 'hola mundo'"
    "echo '$USER'"
    "echo \"Hola $USER\""
    "echo \"Hola $USER en \$HOME\""     # debe fallar por \
    "echo \"$HOME/$USER\""
    "echo '$HOME/$USER'"
    "echo \"'texto'\""
    "echo '\"texto\"'"
    "echo \"\$HOME\""                    # debe fallar por \
    "echo \"hola"
    "echo 'hola"
    "ls ; pwd"
    "echo hola\\mundo"
    "echo \"$USER\"hola'$HOME'"
)

echo -e "==========================="
echo -e "  TEST AUTOMÁTICO MINISHELL"
echo -e "===========================\n"

for cmd in "${tests[@]}"; do
    echo -e "\n💬 Probando comando: $cmd"

    # EJECUCIÓN EN bash
    bash_out=$(echo "$cmd" | bash 2>&1)

    # EJECUCIÓN EN minishell
    mini_out=$(echo "$cmd" | $MINISHELL 2>&1)

    echo -e "\n🟢 Bash:"
    echo "$bash_out"
    echo -e "\n🔵 Minishell:"
    echo "$mini_out"

    if [[ "$bash_out" == "$mini_out" ]]; then
        echo -e "\n✔ Resultado IGUAL"
    else
        echo -e "\n❌ Resultado DIFERENTE"
    fi

    echo -e "----------------------------------"
done
