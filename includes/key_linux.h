/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_linux.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmodrzej <dmodrzej@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 23:19:17 by dmodrzej          #+#    #+#             */
/*   Updated: 2024/12/28 17:25:44 by dmodrzej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_LINUX_H
# define KEY_LINUX_H

# define KEY_PRESS          2
# define KEY_PRESS_MASK     1
# define KEY_RELEASE		3
# define KEY_RELEASE_MASK	2
# define EXPOSE				12
# define NO_EVENT_MASK		0
# define EXPOSURE_MASK		32768
# define CLOSE_BTN			17

/*
** Keyboard LETTERS
*/

# define KEY_A 97
# define KEY_B 98
# define KEY_C 99
# define KEY_D 100
# define KEY_E 101
# define KEY_F 102
# define KEY_G 103
# define KEY_H 104
# define KEY_I 105
# define KEY_J 106
# define KEY_K 107
# define KEY_L 108
# define KEY_M 109
# define KEY_N 110
# define KEY_O 111
# define KEY_P 112
# define KEY_Q 113
# define KEY_R 114
# define KEY_S 115
# define KEY_T 116
# define KEY_U 117
# define KEY_V 118
# define KEY_W 119
# define KEY_X 120
# define KEY_Y 121
# define KEY_Z 122

/*
** Keyboard ARROWS
*/

# define KEY_AR_L 65361
# define KEY_AR_R 65363
# define KEY_AR_U 65362
# define KEY_AR_D 65364

/*
** Keyboard NUMPAD
*/

# define KEY_NP_DIV 65455
# define KEY_NP_MUL 65450
# define KEY_NP_MIN 65453
# define KEY_NP_PLU 65451

/*
** Keyboard MISC
*/

# define KEY_SPACE 32
# define KEY_ESC 65307

/*
** Mouse
*/

# define M_CLK_L 1
# define M_CLK_R 3
# define M_CLK_M 2
# define M_SCR_U 4
# define M_SCR_D 5
# define MOTION_NOTIFY 6
# define POINTER_MOTION_MASK 64

#endif