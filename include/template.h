/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrillar <ltrillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 16:20:24 by ltrillar          #+#    #+#             */
/*   Updated: 2025/10/08 22:32:07 by ltrillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEMPLATE_H
# define TEMPLATE_H

/* ========================== */
/*        COLOR CODES         */
/* ========================== */
# define BOLD_BLACK        "\001\e[1;30m\002"
# define BOLD_RED          "\001\e[1;91m\002"
# define BACKGROUND_YELLOW "\001\e[0;103m\002"
# define BOLD_YELLOW       "\001\e[1;93m\002"
# define BOLD_ROSE         "\001\033[1;35m\002"
# define BOLD_GREEN        "\001\e[1;92m\002"
# define RESET             "\001\e[0m\002"

/* ========================== */
/*        PROMPTS & UI        */
/* ========================== */
# define TEMPLATE_PROMPT BOLD_GREEN "➜ " RESET BACKGROUND_YELLOW BOLD_BLACK " " 
# define TEMPLATE_PROMPT_END " " RESET BOLD_YELLOW " $> " RESET

#endif /* TEMPLATE_H */