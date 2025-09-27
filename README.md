🗂️ Schéma de départ pour Minishell
1. Boucle principale (REPL)

    Afficher un prompt (readline()).

    Lire la commande entrée par l’utilisateur.

    Ajouter la commande à l’historique (add_history()).

    Si CTRL+D → quitter proprement.

2. Parsing

    Tokenisation : découper la ligne en mots (en tenant compte des quotes ' ").

    Expansion :

        $VAR → remplacer par valeur d’environnement.

        $? → remplacer par le dernier code de retour.

    Gestion des quotes :

        '...' → littéral.

        "..." → expansion $ autorisée.

    Redirections :

        <, >, >>, <<.

    Pipes :

        Découper en plusieurs commandes reliées.

3. Exécution

    Vérifier si la commande est un built-in :

        echo, cd, pwd, export, unset, env, exit.

        → Exécuter directement dans le processus parent (pas de fork pour cd, exit, export, etc.).

    Sinon :

        Fork un processus enfant.

        Dans l’enfant → execve() avec le bon chemin (trouvé via $PATH ou absolu/relatif).

        Dans le parent → waitpid() pour attendre la fin (sauf si background jobs, bonus).

4. Redirections & Pipes

    Avant execve() :

        Si < → dup2(fd_in, STDIN_FILENO).

        Si > → dup2(fd_out, STDOUT_FILENO).

        Si >> → ouvrir en mode append.

        Si << → gérer heredoc (lecture jusqu’au délimiteur).

    Pour | :

        Créer un pipe().

        Connecter stdout du premier à stdin du suivant.

5. Gestion des signaux

    SIGINT (Ctrl-C) → afficher un nouveau prompt.

    SIGQUIT (Ctrl-\) → ignoré.

    EOF (Ctrl-D) → quitter le shell.

    Utiliser une seule variable globale pour stocker le signal reçu.

6. Environnement

    Stocker les variables d’environnement dans une structure (ex: liste chaînée).

    export → ajouter/modifier.

    unset → supprimer.

    env → afficher.

    Passer l’environnement à execve().

📝 Vue d’ensemble (pseudo-code)
c
