/*******************************************************************************
 * Licensed Materials - Property of Lorenzo Gatti & Massimo Maiolo
 *
 *
 * Copyright (C) 2015-2018 by Lorenzo Gatti & Massimo Maiolo
 *******************************************************************************
 *
 * This file is part of miniJATI
 *
 * miniJATI is a free software: you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * miniJATI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with miniJATI. If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************/

/**
 * @file DistanceFactoryAlign.hpp
 * @author Adam Szalkowski
 * @author Massimo Maiolo
 * @date 06 08 2020
 * @version 1.0.7
 * @maintainer Lorenzo Gatti
 * @email lg@lorenzogatti.me
 * @maintainer Massimo Maiolo
 * @email massimo.maiolo@zhaw.ch
 * @status Development
 *
 * @brief
 * @details
 * @pre
 * @bug
 * @warning
 *
 * @see For more information visit:
 */

#ifndef CASTOR_DISTANCEFACTORYALIGN_HPP
#define CASTOR_DISTANCEFACTORYALIGN_HPP

#include "DistanceFactory.hpp"
#include "DistanceFactoryML.hpp"
#include <glog/logging.h>

namespace DistanceFactoryPrographMSA {

    class DistanceFactoryAlign : public DistanceFactoryML {

    private:
        typedef int dp_int_t;
        typedef Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> DynProgMatrix;
        typedef typename DistanceFactoryML::CountMatrix CountMatrix;

        int ALPHABET_DIM_;
        Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> scoring_matrix;

    public:

        DistanceFactoryAlign(bpp::SubstitutionModel *smodel, int ALPHABET_DIM) : DistanceFactoryML(smodel,
                                                                                                   ALPHABET_DIM) {

            if (ALPHABET_DIM == 4) {
                initMatrix_DNA();
            } else if (ALPHABET_DIM == 20) {
                initMatrix_AA();
            } else {
                initMatrix_Codon();
            }

            this->ALPHABET_DIM_ = ALPHABET_DIM;
            scoring_matrix.resize(ALPHABET_DIM + 1, ALPHABET_DIM + 1);

        };

        virtual ~DistanceFactoryAlign() {};

        virtual DistanceMatrix computePwDistances(bpp::SequenceContainer *sequences,
                                                  int ALPHABET_DIM,
                                                  int K,
                                                  bool mldist_flag,
                                                  bool mldist_gap_flag,
                                                  double cutoff_dist,
                                                  double indel_rate);

    protected:

        distvar_t alignPair(const std::string &seq1,
                            const std::string &seq2,
                            bool mldist_flag,
                            bool mldist_gap_flag,
                            double cutoff_dist,
                            double indel_rate);

        void initMatrix_AA();

        void initMatrix_DNA();

        void initMatrix_Codon();

        int gap_open;
        int gap_extend;

    };

}

#endif //CASTOR_DISTANCEFACTORYALIGN_HPP
