/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:20:24 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/13 20:21:58 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPLATE_H
# define TEMPLATE_H

/* ========================== */
/*        COLOR CODES         */
/* ========================== */
# define BOLD_BLACK        "\001\e[1;30m\002"
# define BOLD_RED          "\001\e[1;91m\002"
# define BACKGROUND_BLUE "\001\e[0;104m\002"
# define BOLD_ROSE         "\001\033[1;35m\002"
# define BOLD_GREEN        "\001\e[1;92m\002"
# define BOLD_WHITE         "\001\e[1;97m\002"
# define RESET             "\001\e[0m\002"

/* ========================== */
/*        PROMPTS & UI        */
/* ========================== */
# define TEMPLATE_PROMPT BOLD_GREEN "➜ " RESET BACKGROUND_BLUE BOLD_WHITE " " 
# define TEMPLATE_PROMPT_END " " RESET BOLD_GREEN " $> " RESET

#endif /* TEMPLATE_H */