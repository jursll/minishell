/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:46:36 by julrusse          #+#    #+#             */
/*   Updated: 2025/04/11 14:36:07 by julrusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/builtin.h"
#include <stdio.h>

int main(void)
{
    int ret;
    char cwd[MAX_PATH];

    // Test 1 : appel de pwd sans argument
    // On s'attend à ce que pwd affiche le répertoire courant et retourne 0.
    char *args1[] = {"pwd", NULL};
    ret = builtin_pwd(args1);
    if (ret == 0)
    {
        // On récupère le répertoire courant pour affichage
        if (getcwd(cwd, sizeof(cwd)))
            printf("Test 1 : Répertoire actuel (pwd sans argument) : %s\n", cwd);
        else
            printf("Test 1 : Erreur getcwd après pwd\n");
        printf("Test 1 : pwd sans argument réussi\n");
    }
    else
    {
        printf("Test 1 : pwd sans argument échoué\n");
    }

    // Test 2 : appel de pwd avec un argument supplémentaire
    // Comme pwd ne doit accepter aucun argument, on s'attend à un message d'erreur
    char *args2[] = {"pwd", "extra", NULL};
    ret = builtin_pwd(args2);
    if (ret != 0)
        printf("Test 2 : pwd avec argument supplémentaire a échoué (attendu)\n");
    else
        printf("Test 2 : pwd avec argument supplémentaire a réussi (inattendu)\n");

    return 0;
}

