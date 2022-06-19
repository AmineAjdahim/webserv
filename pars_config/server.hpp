/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: majdahim <majdahim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:20:04 by majdahim          #+#    #+#             */
/*   Updated: 2022/06/19 20:00:16 by majdahim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../config.hpp"
#include <fstream>

class Server : public Config
{
    public:
    std::vector<_location> _locations;
        Server(void);
        ~Server(void);
        void get_config(void);
        
};
