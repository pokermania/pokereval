/*
 * Copyright (C) 2004 Mekensleep
 *
 * Mekensleep
 * 24 rue vieille du temple
 * 75004 Paris
 *       licensing@mekensleep.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 * Authors:
 *  Loic Dachary <loic@gnu.org>
 *
 */ 

#ifndef LIBPOKEREVAL_EXPORT
#define LIBPOKEREVAL_EXPORT 1


#if defined(_MSC_VER)
    #pragma warning( disable : 4244 )
    #pragma warning( disable : 4251 )
    #pragma warning( disable : 4267 )
    #pragma warning( disable : 4275 )
    #pragma warning( disable : 4290 )
    #pragma warning( disable : 4786 )
    #pragma warning( disable : 4305 )
#endif

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
	#  ifdef POKEREVAL_LIBRARY
	#    define POKEREVAL_EXPORT   __declspec(dllexport)
        #    define RANDOM rand
	#  else
	#    ifdef __cplusplus
	#       define POKEREVAL_EXPORT   "C" __declspec(dllimport)
        #    else
	#       define POKEREVAL_EXPORT   __declspec(dllimport)
        #    endif
	#  endif /* POKEREVAL_LIBRARY */
#else
	#  define POKEREVAL_EXPORT
#endif  


#endif
